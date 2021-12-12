// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaking.generated.h"

UCLASS()
class POSTPROJECT_API UEnvQueryTest_PickupCouldBeTaking : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UEnvQueryTest_PickupCouldBeTaking(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const;
};
