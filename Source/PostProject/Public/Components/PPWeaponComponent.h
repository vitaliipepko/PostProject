// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PPBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "PPCoreTypes.h"
#include "PPWeaponComponent.generated.h"

class APPBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POSTPROJECT_API UPPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<APPBaseWeapon>WeaponType, int32 ClipsAmount);
	bool NeedAmmo(TSubclassOf<APPBaseWeapon>WeaponType);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	APPBaseWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY()
	TArray<APPBaseWeapon*> Weapons;
	
	UPROPERTY()
	UAnimMontage* ReloadAnimMontage;

	int32 CurrentWeaponIndex = 0;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);

private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	
	void SpawnWeapons();

	void AttachWeaponToSocket(APPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const;

	void OnEmptyClip(APPBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();
};
