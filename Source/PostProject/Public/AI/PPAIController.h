// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PPAIController.generated.h"

class UPPAIPerceptionComponent;

UCLASS()
class POSTPROJECT_API APPAIController : public AAIController
{
	GENERATED_BODY()

	APPAIController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UPPAIPerceptionComponent* PPAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};
