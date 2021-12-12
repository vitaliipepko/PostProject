// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/PPChangeWeaponService.h"
#include "Components/PPWeaponComponent.h"
#include "AIController.h"
#include "PPUtils.h"

UPPChangeWeaponService::UPPChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UPPChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}