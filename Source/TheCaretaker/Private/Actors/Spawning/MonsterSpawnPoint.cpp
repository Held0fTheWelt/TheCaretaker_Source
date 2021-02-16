/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "MonsterSpawnPoint.h"

#include "Actors/Monsters/TutorialFeedingVolumeActor.h"
#include "GameFramework/Actor.h"
#include "Log/GlobalLog.h"

void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (MonsterPawn == nullptr)
	{
		LOG_WARNING(InitializationLog, "Monster Pawn was null. Is it set up in the scene ?")
	}
	else
	{
		MonsterPawn->SetActorHiddenInGame(true);
	}

	if (FeedingVolume == nullptr)
	{
		LOG_WARNING(InitializationLog, "Feeding Volume was null. Is it set up in the scene ?")
	}
	else
	{
		FeedingVolume->SetActorHiddenInGame(true);
	}
}

void AMonsterSpawnPoint::ShowMonster()
{
	if (MonsterPawn == nullptr)
	{
		LOG_WARNING(InitializationLog, "Monster Pawn was null. Is it set up in the scene ?")
	}
	else
	{
		MonsterPawn->SetActorHiddenInGame(false);
	}

	if (FeedingVolume == nullptr)
	{
		LOG_WARNING(InitializationLog, "Feeding Volume was null. Is it set up in the scene ?")
	}
	else
	{
		FeedingVolume->SetActorHiddenInGame(false);
		FeedingVolume->InitMarkerWidget();
	}
}
