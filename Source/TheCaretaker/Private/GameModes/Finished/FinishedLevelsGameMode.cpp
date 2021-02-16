/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "FinishedLevelsGameMode.h"

#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void AFinishedLevelsGameMode::BeginPlay()
{
	Super::BeginPlay();

	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance.")
	}
	else
	{
		GameInstance->CalculateCurrentDifficulty();
	}
}