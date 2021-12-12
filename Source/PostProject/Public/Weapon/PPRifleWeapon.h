// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PPBaseWeapon.h"
#include "PPRifleWeapon.generated.h"

class UPPWeaponFXComponent;
class UNiagaraComponent;
class UAudioComponent;

UCLASS()
class POSTPROJECT_API APPRifleWeapon : public APPBaseWeapon
{
	GENERATED_BODY()

public:
	APPRifleWeapon();
	
	virtual void StartFire() override;
	virtual void StopFire()override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float DamageAmount = FMath::RandRange(10.0f, 25.0f);

	UPROPERTY(VisibleAnywhere, Category="VFX")
	UPPWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	virtual void MakeShot()override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void MakeDamage(const FHitResult& HitResult);
	void InitFx();
	void SetFXActive(bool IsActive);
};
