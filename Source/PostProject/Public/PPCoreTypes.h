#pragma once
#include "PPCoreTypes.generated.h"

//Weapon

class APPBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, APPBaseWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	TSubclassOf<APPBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* CrossHairIcon;
};

//Health

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);


//VFX

class UNiagaraSystem;
class USoundCue;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="VFX")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="VFX")
	float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="VFX")
	FDecalData DecalData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="VFX")
	USoundCue* Sound;
};

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersNum = 2;
};