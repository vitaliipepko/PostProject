// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPCoreTypes.h"
#include "PP_PlayerHUDWidget.generated.h"

UCLASS()
class POSTPROJECT_API UPP_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=UI)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category=UI)
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category=UI)
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category=UI)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category=UI)
    bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void OnTakeDamage();
    
    virtual bool Initialize() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
};
