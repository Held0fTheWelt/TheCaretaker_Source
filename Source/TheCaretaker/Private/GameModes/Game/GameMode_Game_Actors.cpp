/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameMode_Game.h"

#include "Actors/Monsters/MonsterFeedingVolumeActor.h"
#include "Components/Clock/ClockComponent.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/Game/GameFunctionsInterface.h"
#include "Interfaces/Monsters/Feeding/MonsterFeedingInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"


#pragma region NewGame

void AGameMode_Game::BroadcastNewGameStart(UWorld* World)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(World, UGameFunctionsInterface::StaticClass(), Actors);
	//LOG_WARNING(RuntimeExecutionLog, "Block to lay out later !");

	for (auto Actor : Actors)
	{
		IGameFunctionsInterface* ActorToStart = Cast<IGameFunctionsInterface>(Actor);
		
		if (ActorToStart == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameMode could not start actor! Pointer was null !");
			continue;
		}

		ActorToStart->NewGame();
	}
}
#pragma endregion

#pragma region Setup Monsters To Feed
void AGameMode_Game::RegisterMonstersToFeed(UWorld* World)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(World, UMonsterFeedingInterface::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		AMonsterFeedingVolumeActor* MonsterFeedingVolume = Cast<AMonsterFeedingVolumeActor>(Actor);
		if (MonsterFeedingVolume == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameMode could cast actor to MonsterInterface! Cannot setup instance!");
			continue;
		}

		GameInstanceUI->GetNewProgressBarWidget(MonsterFeedingVolume->FeedingUIWidget);
		MonsterFeedingVolume->InitializationComplete();
	}
}
#pragma endregion


void AGameMode_Game::SetGamePaused(bool SetGamePaused)
{
	bPaused = SetGamePaused;

	ClockComponent->SetGamePaused(!bPaused);
}

bool AGameMode_Game::IsPaused() const
{
	return bPaused;
}


