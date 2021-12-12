// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PPBasePickup.h"
#include "PPHealthPickup.generated.h"

UCLASS()
class POSTPROJECT_API APPHealthPickup : public APPBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 100.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
