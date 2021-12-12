// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PPProjectile.h"
#include "Weapon/PPBaseWeapon.h"
#include "PPLauncherWeapon.generated.h"

class APPProjectile;
class USoundCue;

UCLASS()
class POSTPROJECT_API APPLauncherWeapon : public APPBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<APPProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	USoundCue* NoAmmoSound;
	
	virtual void MakeShot() override;
};
