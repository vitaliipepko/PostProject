// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGameInstance.h"
#include "Sound/PPSoundFuncLib.h"

void UPPGameInstance::ToggleVolume()
{
	UPPSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}