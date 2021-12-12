// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/PPSoundFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPSoundFuncLib, All, All);

void UPPSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);

	UE_LOG(LogPPSoundFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
}

void UPPSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if(!SoundClass) return;

	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	SetSoundClassVolume(SoundClass, NextVolume);
}