/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "LockedByLevelPointsActor.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ALockedByLevelPointsActor::ALockedByLevelPointsActor()
{
	PrimaryActorTick.bCanEverTick = false;

	LevelPointsToUnlock = 0;


}

void ALockedByLevelPointsActor::BeginPlay()
{
	Super::BeginPlay();
	
	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance was null ! This shouldn't happen !")
	}
	else
	{
		if (!(GameInstance->GetCurrentLevelPoints() >= LevelPointsToUnlock))
		{
			for (auto Actor : ActorsToHideUntilCompletion)
			{
				if (Actor == nullptr)
				{
					continue;
				}
				Actor->Destroy();
			}
		}
	}

}
