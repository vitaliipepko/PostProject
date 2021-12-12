// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PPRifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Player/PPBaseCharacter.h"
#include "Weapon/Components/PPWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

APPRifleWeapon::APPRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UPPWeaponFXComponent>("WeaponFXComponent");
}

void APPRifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}


void APPRifleWeapon::StartFire()
{
	InitFx();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APPRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void APPRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetFXActive(false);
}

void APPRifleWeapon::MakeShot()
{
	if(!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult,TraceStart, TraceEnd);

	if(HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}else
	{
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
	DecreaseAmmo();
}

bool APPRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void APPRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if(!DamagedActor) return;

	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo = HitResult;
	DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetPlayerController(), this);
}

void APPRifleWeapon::InitFx()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if(!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	
	SetFXActive(true);
}

void APPRifleWeapon::SetFXActive(bool IsActive)
{
	if(MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);
		MuzzleFXComponent->SetVisibility(IsActive, true);
	}

	if(FireAudioComponent)
	{
		IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
	}
}
