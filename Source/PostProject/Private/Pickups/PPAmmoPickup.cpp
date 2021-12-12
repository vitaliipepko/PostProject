// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PPAmmoPickup.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"
#include "PPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool APPAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}