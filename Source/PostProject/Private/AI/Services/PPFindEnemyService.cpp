// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/PPFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PPAIPerceptionComponent.h"
#include "PPUtils.h"

UPPFindEnemyService::UPPFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UPPFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Display, TEXT("find enemy"));
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = PPUtils::GetPPPlayerComponent<UPPAIPerceptionComponent>(Controller);
		if(PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}