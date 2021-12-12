// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PPProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/PPWeaponFXComponent.h"
#include "Kismet/GameplayStatics.h"

APPProjectile::APPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;

	WeaponFXComponent = CreateDefaultSubobject<UPPWeaponFXComponent>("WeaponFXComponent");
}

void APPProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);
	
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &APPProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
}

void APPProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if(!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	//make damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), //
		DamageAmount, //
		GetActorLocation(), //
		DamageRadius, //
		UDamageType::StaticClass(), //
		{GetOwner()}, //
		this, //
		GetController(), //
		DoFullDamage);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
	WeaponFXComponent->PlayImpactFX(Hit);
	
	Destroy();
}

AController* APPProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}