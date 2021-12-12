// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PPCharacterMovementComponent.h"
#include "Components/PPHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PPWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(TestCharacterLog, All, All);

APPBaseCharacter::APPBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<UPPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UPPHealthComponent>("HealthComponent");

	WeaponComponent = CreateDefaultSubobject<UPPWeaponComponent>("WeaponComponent");
}

void APPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &APPBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &APPBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &APPBaseCharacter::OnGroundLanded);
}

void APPBaseCharacter::OnHealthChanged(float Health, float OHealthDelta) 
{
	
}

void APPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APPBaseCharacter::IsRunning() const
{
	return false;
}

float APPBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void APPBaseCharacter::OnDeath() 
{
	UE_LOG(TestCharacterLog, Display, TEXT("Player is dead"), *GetName());

	//PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void APPBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(TestCharacterLog, Display, TEXT("On landed:%f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(TestCharacterLog, Display, TEXT("FinalDamage:%f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
