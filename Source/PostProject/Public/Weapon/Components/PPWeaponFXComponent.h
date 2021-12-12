// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraSystem.h"
#include "CoreTypes.h"
#include "PPCoreTypes.h"
#include "PPWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POSTPROJECT_API UPPWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
