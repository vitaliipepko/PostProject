// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PPWeaponComponent.h"
#include "Weapon/PPBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/PPEquipFinishedAnimNotify.h"
#include "Animations/PPReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

UPPWeaponComponent::UPPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);

	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UPPWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for(auto Weapon:Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	
	Super::EndPlay(EndPlayReason);
}

void UPPWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || !GetWorld()) return;

	for(auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<APPBaseWeapon>(OneWeaponData.WeaponClass);
		if(!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &UPPWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UPPWeaponComponent::AttachWeaponToSocket(APPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if(!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UPPWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Display, TEXT("Invalid weapon index"));
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if(CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data){return Data.WeaponClass == CurrentWeapon->GetClass();});

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UPPWeaponComponent::StartFire()
{
	if(!CanFire()) return;
	CurrentWeapon->StartFire();
}

void UPPWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UPPWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UPPWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;
	
	Character->PlayAnimMontage(Animation);
}

void UPPWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UPPEquipFinishedAnimNotify>(EquipAnimMontage);
	if(EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UPPWeaponComponent::OnEquipFinished);
	}else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}

	for (auto OneWeaponData:WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UPPReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if(!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UPPWeaponComponent::OnReloadFinished);
	}
}

void UPPWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || Character->GetMesh() != MeshComponent) return;

	EquipAnimInProgress = false;
}

void UPPWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || Character->GetMesh() != MeshComponent) return;

	ReloadAnimInProgress = false;
}

bool UPPWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UPPWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UPPWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UPPWeaponComponent::Reload()
{
	ChangeClip();
}

void UPPWeaponComponent::OnEmptyClip(APPBaseWeapon* AmmoEmptyWeapon)
{
	if(!AmmoEmptyWeapon) return;
	
	if(CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for(const auto Weapon : Weapons)
		{
			if(Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
}

void UPPWeaponComponent::ChangeClip()
{
	if(!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool UPPWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if(CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool UPPWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if(CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

bool UPPWeaponComponent::TryToAddAmmo(TSubclassOf<APPBaseWeapon>WeaponType, int32 ClipsAmount)
{
	for(const auto Weapon: Weapons)
	{
		if(Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}

bool UPPWeaponComponent::NeedAmmo(TSubclassOf<APPBaseWeapon>WeaponType)
{
	for(const auto Weapon: Weapons)
	{
		if(Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}