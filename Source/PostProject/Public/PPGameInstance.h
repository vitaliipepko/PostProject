// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPGameInstance.generated.h"

class USoundClass;

UCLASS()
class POSTPROJECT_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void ToggleVolume();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundClass* MasterSoundClass;
	
};
