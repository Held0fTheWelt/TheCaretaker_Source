/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "States/Game/CaretakerGameState.h"

#include "TimerManager.h"

#include "Actors/Fireplace/FireplaceActor.h"
#include "Actors/WinCondition/WinConditionActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "Engine/GameInstance.h"
#include "Characters/DungeonMaster/DungeonMasterCharacter.h"
#include "GameInstance/GameInstanceManager.h"
#include "Interfaces/WinCondition/WinConditionVolumeInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"
#include "States/Player/CaretakerPlayerState.h"
#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"
#include "Widgets/Information/InformationWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Widgets/Main/MainUI.h"

void ACaretakerGameState::SetupScore()
{
	if (GameInstanceInterface == nullptr)
	{
		UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
		GameInstanceInterface = Cast<IGameInstanceAccessoryInterface>(Instance);
	}

	if (GameInstanceInterface == nullptr)
	{
		LOG_WARNING(InitializationLog,"GameInstanceInterface was nullptr ! this shouldn't happen !")
		return;
	}

	if (ScoreDefinition == nullptr || ScoreMultiplier == nullptr || TimeToScore == nullptr)
	{
		bScoreSetupOkay = false;
	}
	else
	{
		ReadInScoreSetup();
		CurrentScoreWidget = GameInstanceInterface->AddScoreWidget();
		if (CurrentScoreWidget == nullptr)
		{
			LOG_WARNING(InitializationLog, "ScoreWidget was null ! This shouldn't happen !")
			bScoreSetupOkay = false;
		}
		else
		{

			bScoreSetupOkay = true;
		}
	}
}

void ACaretakerGameState::NotCompeting()
{
	bScoreSetupOkay = false;
}

void ACaretakerGameState::SetShouldWaitForEndOfTime(bool ShouldWaitForEndOfTime)
{
	bShouldWaitForEndOfTime = ShouldWaitForEndOfTime;
}

void ACaretakerGameState::SetCurrentPart(EPartInformation Part)
{
	CurrentPart = Part;
}
void ACaretakerGameState::SetCurrentDungeon(int32 Dungeon)
{
	CurrentDungeon = Dungeon;
}
void ACaretakerGameState::SetCurrentLevel(int32 Level)
{
	CurrentLevel = Level;
}
int32 ACaretakerGameState::GetCurrentDifficulty() const
{
	return CurrentDifficulty;
}

EPartInformation ACaretakerGameState::GetCurrentPart() const
{
	return CurrentPart;
}

int32 ACaretakerGameState::GetCurrentDungeon() const
{
	return CurrentDungeon;
}

int32 ACaretakerGameState::GetCurrentLevel() const
{
	return CurrentLevel;
}

void ACaretakerGameState::UpdateCurrentInfos(FCurrentProgress CurrentProgress)
{
	CurrentLevel = CurrentProgress.CurrentLevel;
	CurrentDungeon = CurrentProgress.CurrentDungeon;
	CurrentPart = CurrentProgress.CurrentPart;
	//GameStateInterface->SetShouldWaitForEndOfTime();
}

void ACaretakerGameState::CountVictory()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	Menu->CountAchievement(EAchievementType::AT_VICTORY);
}

bool ACaretakerGameState::WinConditionMet() const
{
	if (GarbageCount == 0
		&& TrapCount == 0
		&& ChestCount == 0)
	{
		return true;
	}

	return false;
}

void ACaretakerGameState::ShowNewCredentials()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MenuGameInstance was null ! This shouldn't happen !")
		return;
	}

	if (Menu->CompletedCurrentLevel())
	{
		Menu->ShowNewCredentials();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowCredentials, this, &ACaretakerGameState::PerformLevelChange, .1f, false, TimeToShowCredentials);
	}
	else
	{
		PerformLevelChange();
	}
}



void ACaretakerGameState::HideFinalScore()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"MenuInstance was null ! This shouldn't happen !")
	}
	else
	{
		Menu->HideFinalScore();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowCredentials, this, &ACaretakerGameState::ShowHighScore, .1f, false, .5f);
	}
}

int8 ACaretakerGameState::GetCurrentChestCount() const
{
	return ChestCount;
}
