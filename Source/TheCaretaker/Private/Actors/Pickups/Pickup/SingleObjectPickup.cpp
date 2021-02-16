/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SingleObjectPickup.h"

#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ASingleObjectPickup::ASingleObjectPickup()
{
	PowerUpClass = nullptr;
	LevelPointsToUnlock = 0;
}

void ASingleObjectPickup::BeginPlay()
{
	Super::BeginPlay();

	Accessory = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Accessory == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameInstance ! This shouldn't happen !")
	}
	else
	{
		if (LevelPointsToUnlock > Accessory->GetCurrentLevelPoints())
		{
			LOG_WARNING(InitializationLog, "Not enough LevelPoints. Destroying")
			UE_LOG(LogTemp, Warning, TEXT("%s, Current LevelPoints to Unlock: %d LevelPoints: %d"), *GetName(), LevelPointsToUnlock, Accessory->GetCurrentLevelPoints());
			Destroy();
			return;
		}
	}

	//if (bHasFirstValuesSet == false)
	//{
	//	bHasFirstValuesSet = true;
	//	SetSpawnLocation(GetActorLocation());
	//}

	//SetActorLocation(SpawnLocation);
}

void ASingleObjectPickup::Respawn()
{
	if (PowerUpClass != nullptr)
	{
		CurrentPowerUpClass = PowerUpClass;

		Super::Respawn();
	}
	else
	{
		LOG_WARNING(InitializationLog, "Could not respawn, because Power Up Class is null. Is it set in the blueprint an level ?")
	}
}

void ASingleObjectPickup::KillPowerUpActor()
{
	if (CurrentPowerUpActor != nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "No PowerUp Actor. Continuing")
	}
	else
	{
		CurrentPowerUpActor->Destroy();
		CurrentPowerUpActor = nullptr;
		LOG_WARNING(RuntimeExecutionLog, "PowerUpActor destroyed")
	}
}

void ASingleObjectPickup::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	LOG_WARNING(RuntimeExecutionLog, "Clicked Pickup")

	if (CurrentPowerUpActor == nullptr)
	{

	}
	else
	{
		if (Accessory == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not find GameInstance ! This shouldn't happen !")
		}
		else
		{
			Accessory->PickupCollected(PowerUpClass);
			CurrentPowerUpActor->Destroy();
			CurrentPowerUpActor = nullptr;
			Destroy();
		}
	}
}

void ASingleObjectPickup::SetSpawnLocation(FVector NewSpawnLocation)
{
	SpawnLocation = NewSpawnLocation;
}
