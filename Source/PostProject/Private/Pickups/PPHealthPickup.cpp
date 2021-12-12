// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PPHealthPickup.h"
#include "Components/PPHealthComponent.h"
#include "PPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool APPHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;
	
	return HealthComponent->TryToAddHealth(HealthAmount);
}