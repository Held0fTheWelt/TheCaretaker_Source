/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "DungeonMasterVisibleOnMap.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/DungeonMaster/DungeonMasterCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "Controllers/AI/SimpleChaseAIController.h"
#include "Engine/World.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "States/Game/CaretakerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ADungeonMasterVisibleOnMap::ADungeonMasterVisibleOnMap()
{
	if (SpawnPointForDungeonMaster == nullptr)
	{
		SpawnPointForDungeonMaster = CreateDefaultSubobject<USceneComponent>(FName("SpawnPoint"));
	}

	SpawnPointForDungeonMaster->SetupAttachment(RootComponent);

	if (AudioComponent == nullptr)
		AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("AudioComponent"));

	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetRelativeLocation(FVector(FMath::RandRange(-200.f,200.f), FMath::RandRange(-200.f, 200.f), -50.f));

	VolumeForMasterSleep = 1.f;
	VolumeForMasterWakeUp = 1.f;

	DungeonMasterAITemplate = nullptr;
	DungeonMasterAITemplate = nullptr;

	DungeonMasterSleep = nullptr;
	DungeonMasterWakeUp = nullptr;

	bMasterSleepIsUISound = false;
	bMasterAwakeIsUISound = false;
}

void ADungeonMasterVisibleOnMap::BeginPlay()
{
	Super::BeginPlay();

	if (DungeonMasterSleep == nullptr)
	{
		LOG_WARNING(InitializationLog, "DungeonMaster Sleep Sound was null ! Can't play dungeon master is sleeping.")
	}
	else
	{
		AudioComponent->SetSound(DungeonMasterSleep);
		AudioComponent->SetVolumeMultiplier(VolumeForMasterSleep);
		AudioComponent->SetUISound(bMasterSleepIsUISound);
		AudioComponent->Play();
	}
}

void ADungeonMasterVisibleOnMap::SpawnChasingDungeonMaster()
{
	if (DungeonMasterTemplate == nullptr || DungeonMasterAITemplate == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"A Template was null!")
	}
	else
	{
		if (DungeonMasterWakeUp == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not play WakeUp Sound, because it is not set in blueprint")
		}
		else
		{
			AudioComponent->SetSound(DungeonMasterWakeUp);
			AudioComponent->SetVolumeMultiplier(VolumeForMasterWakeUp);
			AudioComponent->SetUISound(bMasterAwakeIsUISound);
			AudioComponent->Play();
		}

		if (DungeonMasterTemplate == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "DungeonMasterTemplate was null")
			return;
		}
		if (DungeonMasterAITemplate == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "DungeonMasterAITemplate was null")
			return;
		}
		if (SpawnPointForDungeonMaster == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "SpawnPointForDUngeonMaster was null")
			return;
		}

		ADungeonMasterCharacter* DungeonMaster =  Cast<ADungeonMasterCharacter>(UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), DungeonMasterTemplate, nullptr, SpawnPointForDungeonMaster->GetComponentLocation(), SpawnPointForDungeonMaster->GetComponentRotation()));

		AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(GetWorld());

		if (GameStateBase == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog,"GameState was null!")
		}
		else
		{
			IGameStateInterface* GameState = Cast<IGameStateInterface>(GameStateBase);
			if (GameState == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog,"GameState could not be cast to interface!")
			}
			else
			{
				GameState->RegisterDungeonMaster(DungeonMaster);
			}
		}
	}
}
