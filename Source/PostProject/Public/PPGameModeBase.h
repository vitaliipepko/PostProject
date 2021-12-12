// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPCoreTypes.h"
#include "PPGameModeBase.generated.h"

class AAIController;

UCLASS()
class POSTPROJECT_API APPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APPGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	FGameData GameData;

private:
	void SpawnBots();
};
