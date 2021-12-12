// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PPBaseWeapon.h"
#include "BehaviorTree/BTDecorator.h"
#include "PPNeedAmmoDecorator.generated.h"

UCLASS()
class POSTPROJECT_API UPPNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPPNeedAmmoDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<APPBaseWeapon> WeaponType;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
