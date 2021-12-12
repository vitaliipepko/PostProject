// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PPAnimNotify.h"

void UPPAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}