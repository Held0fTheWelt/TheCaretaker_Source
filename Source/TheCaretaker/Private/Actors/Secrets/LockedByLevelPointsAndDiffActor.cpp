// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "LockedByLevelPointsAndDiffActor.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
// Sets default values
ALockedByLevelPointsAndDiffActor::ALockedByLevelPointsAndDiffActor()
{
	PrimaryActorTick.bCanEverTick = false;

	LevelPointsToUnlock = 0;
	DifficultyToUnlock = 0;
}

void ALockedByLevelPointsAndDiffActor::BeginPlay()
{
	Super::BeginPlay();

	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance was null ! This shouldn't happen !")
	}
	else
	{
		if (GameInstance->GetPlayMode() == EPlayMode::PM_CLASSIC)
		{
			for (auto Actor : ActorsToHideUntilCompletion)
			{
				if (Actor == nullptr)
				{
					continue;
				}
				Actor->Destroy();
			}
			return;
		}

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
			return;
		}

		if (!(GameInstance->GetCurrentDifficulty() >= DifficultyToUnlock))
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

