// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PPHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShake.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UPPHealthComponent::UPPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UPPHealthComponent::BeginPlay()
{
	check(MaxHealth > 0);
	
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if(ComponentOwner) 
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UPPHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UPPHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UPPHealthComponent::OnTakeRadialDamage);
	}
}

void UPPHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
        class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType,
        AActor* DamageCauser )
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	UE_LOG(LogHealthComponent, Display, TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage, FinalDamage, *BoneName.ToString());
	ApplyDamage(FinalDamage, InstigatedBy);
}

void UPPHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin,
    FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser )
{
	UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
	ApplyDamage(Damage, InstigatedBy);
}

void UPPHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogHealthComponent, Display, TEXT("On any damage: %f"), Damage);
}

void UPPHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if(IsDead()) 
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UPPHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}

void UPPHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if(IsHealthFull() && GetWorld()) 
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UPPHealthComponent::SetHealth(float NewHealth) 
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UPPHealthComponent::TryToAddHealth(float HealthAmount)
{
	if(IsDead() || IsHealthFull()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

bool UPPHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}


void UPPHealthComponent::PlayCameraShake()
{
	if(IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

float UPPHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if(!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName)) return 1.0f;

	const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if(!PhysMaterial || !DamageModifiers.Contains(PhysMaterial)) return 1.0f;

	return DamageModifiers[PhysMaterial];
}

void UPPHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if(!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;
	
	UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage,
		InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}