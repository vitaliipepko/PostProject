// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PPAIController.h"
#include "PPAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PPAIPerceptionComponent.h"

APPAIController:: APPAIController()
{
	PPAIPerceptionComponent = CreateDefaultSubobject<UPPAIPerceptionComponent>("PPPerceptionComponent");
	SetPerceptionComponent(*PPAIPerceptionComponent);
}

void APPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto PPCharacter = Cast<APPAICharacter>(InPawn);
	if(PPCharacter)
	{
		RunBehaviorTree(PPCharacter->BehaviorTreeAsset);
	}
}

void APPAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* APPAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}