// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PPBasePickup.h"
#include "PPAmmoPickup.generated.h"

class APPBaseWeapon;

UCLASS()
class POSTPROJECT_API APPAmmoPickup : public APPBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TSubclassOf<APPBaseWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
