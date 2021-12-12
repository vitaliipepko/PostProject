// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PPWeaponComponent.h"
#include "PPAIWeaponComponent.generated.h"

UCLASS()
class POSTPROJECT_API UPPAIWeaponComponent : public UPPWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
