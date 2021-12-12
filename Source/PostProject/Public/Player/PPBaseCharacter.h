// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PPBaseCharacter.generated.h"


class UPPHealthComponent;
class UPPWeaponComponent;

UCLASS()
class POSTPROJECT_API APPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APPBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPPHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UPPWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);
	
	virtual void BeginPlay() override;
	virtual void OnDeath();

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

private:
	void OnHealthChanged(float Health, float OHealthDelta);

	UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
