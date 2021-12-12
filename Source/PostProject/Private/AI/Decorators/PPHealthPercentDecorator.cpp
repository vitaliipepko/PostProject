// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/PPHealthPercentDecorator.h"
#include "AIController.h"
#include "PPUtils.h"
#include "Components/PPHealthComponent.h"

UPPHealthPercentDecorator::UPPHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool UPPHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}