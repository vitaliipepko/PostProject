// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PPFindEnemyService.generated.h"

UCLASS()
class POSTPROJECT_API UPPFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UPPFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
