// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PP_PlayerHUDWidget.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"
#include "PPUtils.h"

bool UPP_PlayerHUDWidget::Initialize()
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	if(HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPP_PlayerHUDWidget::OnHealthChanged);
	}
	
	return  Super::Initialize();
}

void UPP_PlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
}

float UPP_PlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPP_PlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UPP_PlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UPP_PlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPP_PlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return  Controller && Controller->GetStateName() == NAME_Spectating;
}