// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGameModeBase.h"
#include "PPGameHUD.h"
#include "Player/PPBaseCharacter.h"
#include "Player/PPPlayerController.h"
#include "AIController.h"

APPGameModeBase::APPGameModeBase()
{
	DefaultPawnClass = APPBaseCharacter::StaticClass();
	PlayerControllerClass = APPPlayerController::StaticClass();
	HUDClass = APPGameHUD::StaticClass();
}

void APPGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
}

UClass* APPGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void APPGameModeBase::SpawnBots()
{
	if(!GetWorld()) return;

	for(int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto PPAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(PPAIController);
	}
}

