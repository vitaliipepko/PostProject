// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PPBaseCharacter.h"
#include "PPAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class POSTPROJECT_API APPAICharacter : public APPBaseCharacter
{
	GENERATED_BODY()

public:
	APPAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
};
