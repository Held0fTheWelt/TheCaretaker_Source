/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Controllers/Animation/FirstPersonAnimationController.h"

#include "Engine/World.h"
#include "GameFramework/Character.h"
//#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void UFirstPersonAnimationController::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (PlayerCharacter == nullptr)
	{
		if (!GetPlayerCharacter())
		{
			LOG_WARNING(InitializationLog, "Could not find PlayerController in AnimInstance class. This shouldn't happen !")
			return;
		}
	}
}

void UFirstPersonAnimationController::PlayFootStepSounds()
{
	if (PlayerCharacter == nullptr)
	{
		if (!GetPlayerCharacter())
		{
			LOG_WARNING(RuntimeLog, "Could not find PlayerController in AnimInstance class. This shouldn't happen !")
			return;
		}
	}
}

bool UFirstPersonAnimationController::GetPlayerCharacter()
{
	
	PlayerCharacter = Cast<ACharacter>(TryGetPawnOwner());

	return PlayerCharacter != nullptr;
}

FVector UFirstPersonAnimationController::GetLocationForLinetrace(bool First)
{
	if (First)
	{
		return PlayerCharacter->GetActorLocation();
	}
	else
	{
		return PlayerCharacter->GetActorLocation() - FVector(0,0,150);
	}
}

