// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "LockedByDifficultyActor.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/Pickup/PickupInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

// Sets default values
ALockedByDifficultyActor::ALockedByDifficultyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DifficultyToUnlock = 0;
}

void ALockedByDifficultyActor::BeginPlay()
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
		else
		{
			for (auto Actor : ActorsToHideUntilCompletion)
			{
				if (Actor == nullptr)
				{
					continue;
				}
				IPickupInterface* Pickup = Cast<IPickupInterface>(Actor);

				if (Pickup != nullptr)
				{
					Pickup->Respawn();
				}
				else
				{
					LOG_WARNING(InitializationLog, "Could not cast PickupInterface")
				}
			}
		}
	}
	
}

