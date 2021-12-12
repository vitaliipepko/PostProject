// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/PPNeedAmmoDecorator.h"
#include "AIController.h"
#include "PPUtils.h"
#include "Components/PPWeaponComponent.h"

UPPNeedAmmoDecorator::UPPNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool UPPNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(Controller->GetPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}