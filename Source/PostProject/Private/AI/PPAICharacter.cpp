// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PPAICharacter.h"
#include "AI/PPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PPAIWeaponComponent.h"
#include "BrainComponent.h"

APPAICharacter::APPAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<UPPAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = APPAICharacter::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void APPAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto PPController = Cast<AAIController>(Controller);
	if(PPController && PPController->BrainComponent)
	{
		PPController->BrainComponent->Cleanup();
	}
}