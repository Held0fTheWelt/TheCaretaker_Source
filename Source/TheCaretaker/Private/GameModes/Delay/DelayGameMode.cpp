/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameModes/Delay/DelayGameMode.h"

#include "TimerManager.h"

#include "Engine/World.h"
#include "GameInstance/GameInstanceMenuInterface.h"
#include "Log/GlobalLog.h"

ADelayGameMode::ADelayGameMode()
{
	TimeToFinish = 2.f;
	MapToLoad = EName::NAME_None;
}

void ADelayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DelayTimer, this, &ADelayGameMode::Finish,.1, false, TimeToFinish);
}

void ADelayGameMode::Executed()
{
	Finish();
}

void ADelayGameMode::Finish()
{
	GetWorldTimerManager().ClearTimer(DelayTimer);

	IGameInstanceMenuInterface* GameInstance = Cast<IGameInstanceMenuInterface>(GetGameInstance());


	if (GameInstance != nullptr)
	{
		if (bUseSecondList)
		{
			if (GameInstance->IsPartTwo())
			{
				GameInstance->OpenMap(MapToLoadSecond[0]);
			}
			else
			{
				GameInstance->OpenMap(MapToLoad);
			}
		}
		else
		{
			GameInstance->OpenMap(MapToLoad);
		}
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot find GameInstance!")
	}
}
