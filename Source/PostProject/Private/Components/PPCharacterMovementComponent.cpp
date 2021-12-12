// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PPCharacterMovementComponent.h"
#include "Player/PPBaseCharacter.h"

float UPPCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const APPBaseCharacter* Player = Cast<APPBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
