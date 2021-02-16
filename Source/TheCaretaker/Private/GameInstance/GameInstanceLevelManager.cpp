/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "GameInstance/GameInstanceManager.h"

#include "TimerManager.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Structs/Game/GameInformation.h"

const bool UGameInstanceManager::LoadLevelInformation()
{
	static const FString ContextString(TEXT("Game Information"));
	if (GameInformation == nullptr)
	{LOG_WARNING(InitializationLog, "Could not find GameInformation Table ! This shouldn't happen !")
		return false;
	}
	FGameInformation* GameInformationTable = GameInformation->FindRow<FGameInformation>(FName(TEXT("GameInformation")), ContextString, true);
	if (GameInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not get Game Information Table.Could not Cast GameInformation from Game Information Table.")
		return false;
	}
	LOG_DISPLAY(InitializationLog, "Getting Game Information from Data Table.")
	LevelInformation = GameInformationTable->LevelsInGame;
	EventList = GameInformationTable->FModEventList;
	return true;
}

void UGameInstanceManager::AddExtraLevelGameInformation()
{
	static const FString ContextString(TEXT("Extra Levels"));
	if (ExtraLevelsGameInformation == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find Extra Level GameInformation Table ! This shouldn't happen !")
		return;
	}
	FGameInformation* GameInformationTable = ExtraLevelsGameInformation->FindRow<FGameInformation>(FName(TEXT("ExtraLevels")), ContextString, true);
	if (GameInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not get Extra Level Game Information Table.Could not Cast GameInformation from Game Information Table.")
		return;
	}
	LOG_DISPLAY(InitializationLog, "Getting Game Information from Data Table.")

	for (auto Level : GameInformationTable->LevelsInGame)
	{
		LevelInformation.Add(Level);
	}	

	UE_LOG(LogTemp, Display, TEXT("Now %d levels"), LevelInformation.Num());
}

const bool UGameInstanceManager::LoadPlayModeInformation()
{
	static const FString ContextString(TEXT("Game Information"));
	if (PlayModeInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayModeInformationTable Table ! This shouldn't happen !")
		return false;
	}

	TArray<FPlayModeInformation*> OutRows;

	PlayModeInformationTable->GetAllRows(ContextString, OutRows);
	
	LOG_DISPLAY(InitializationLog, "Loading PlayMode Information.")
	for (auto Row : OutRows)
	{
		PlayModeInformation.Add(*Row);
		//LOG_WARNING(RuntimeLog,"1")
	}

	return true;
}

void UGameInstanceManager::AddExtraLevelPlayModeInformation()
{
	static const FString ContextString(TEXT("Game Information"));
	if (PlayModeInformationTableExtraLevels == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find Extra Levels PlayModeInformationTable Table ! This shouldn't happen !")
		return;
	}

	TArray<FPlayModeInformation*> OutRows;

	PlayModeInformationTableExtraLevels->GetAllRows(ContextString, OutRows);

	LOG_DISPLAY(InitializationLog, "Loading Extra Levels PlayMode Information.")
	for (auto Row : OutRows)
	{
		for (int32 i = 0; i < PlayModeInformation.Num(); i++)
		{
			if (Row->PlayMode == PlayModeInformation[i].PlayMode)
			{
				for (auto Level : Row->Levels)
				{
					PlayModeInformation[i].Levels.Add(Level);
				}
				//UE_LOG(LogTemp, Warning, TEXT("PlayMode %d Now has %d levels"),PlayModeInformation[i].PlayMode, LevelInformation.Num());
			}
		}
	}
}

const bool UGameInstanceManager::LoadPlayModeModifierInformation()
{
	static const FString ContextString(TEXT("Game Information"));
	if (PlayModeModifierInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayModeModifierInformationTable  Table ! This shouldn't happen !")
		return false;
	}

	TArray<FPlayModeModifierInformation*> OutRows;

	PlayModeModifierInformationTable->GetAllRows(ContextString, OutRows);

	LOG_DISPLAY(InitializationLog, "Loading PlayModeModifier Information.")
	for (auto Row : OutRows)
	{
		PlayModeModifiers.Add(*Row);
		//LOG_WARNING(RuntimeLog,"2")
	}

	return true;
}

const bool UGameInstanceManager::LoadCredentialSetup()
{
	static const FString ContextString(TEXT("Game Information"));
	if (SecretCredentialList == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find SecretCredentialList Table ! This shouldn't happen !")
		return false;
	}

	TArray<FSecretConnection*> OutRows;

	SecretCredentialList->GetAllRows(ContextString, OutRows);

	LOG_DISPLAY(InitializationLog, "Loading SecretCredentialList Information.")
	for (auto Row : OutRows)
	{
		SecretConnections.Add(*Row);
		//LOG_WARNING(RuntimeLog,"2")
	}

	return true;
}

const bool UGameInstanceManager::LoadPowerUpSetup()
{
	static const FString ContextString(TEXT("PowerUpList"));
	if (SecretCredentialList == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PowerUp Definition Table ! This shouldn't happen !")
			return false;
	}

	TArray<FPowerUpList*> OutRows;

	SecretCredentialList->GetAllRows(ContextString, OutRows);

	LOG_DISPLAY(InitializationLog, "Loading Power Up Information.")
	for (auto Row : OutRows)
	{
		PowerUpInformationList.Add(*Row);
		//LOG_WARNING(RuntimeLog,"2")
	}

	return true;
}

void UGameInstanceManager::SetPauseMode(bool Pause)
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UPauseGameInterface::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		IPauseGameInterface* Interface = Cast<IPauseGameInterface>(Actor);
		if (Interface == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast Actor to PausGameInterface! This shouldn't happen !");
		}
		else
		{
			Interface->SetGamePaused(Pause);
		}
	}

	TArray<UUserWidget*> Widgets;

	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UPauseGameInterface::StaticClass(), false);

	for (auto Widget : Widgets)
	{
		IPauseGameInterface* Interface = Cast<IPauseGameInterface>(Widget);
		if (Interface == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast Widget to PausGameInterface! This shouldn't happen !");
		}
		else
		{
			Interface->SetGamePaused(Pause);
		}
	}
}

void UGameInstanceManager::PerformLevelChange()
{
	LOG_DISPLAY(RuntimeExecutionLog, "Performing Level change !")

	bool Continue = CountCurrentProgress();

	LOG_DISPLAY(RuntimeExecutionLog, "Saving GameData!")

	SaveGameData();

//	if(Continue)

	LOG_DISPLAY(RuntimeExecutionLog, "Load new level after delay!")

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_LevelChangeDelay, this, &UGameInstanceManager::PerformLevelChangeDelay, LevelChangeDelay,false);
}

void UGameInstanceManager::ContinueForced()
{
	IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameStateInterface. This shouldn't happen!")
	}
	else
	{
		GameStateInterface->StopCredentialTimer();
	}
	
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_LevelChangeDelay))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LevelChangeDelay);
	}
	
	LOG_DISPLAY(RuntimeExecutionLog, "Performing Level change !")

	bool Continue = CountCurrentProgress();

	LOG_DISPLAY(RuntimeExecutionLog, "Saving GameData!")

	SaveGameData();

	PerformLevelChangeDelay();
}



bool UGameInstanceManager::CountCurrentProgress()
{
	uint8 currentValue = CurrentProgress.CurrentPart;
	currentValue++;

	if (currentValue == EPartInformation::EPI_END)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "End of Parts reached")
		CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL1;
		currentValue = CurrentProgress.CurrentDungeon;
		currentValue++;

		if (currentValue >= LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel.Num())
		{
			LOG_DISPLAY(RuntimeExecutionLog, "End of Dungeons reached")
			CurrentProgress.CurrentDungeon = 0;
			currentValue = CurrentProgress.CurrentLevel;
			currentValue++;

			if (currentValue >= LevelInformation.Num())
			{
				LOG_WARNING(RuntimeExecutionLog, "Reached End of Game !")
				CurrentProgress.CurrentDungeon = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() - 1;
				CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL3;
				CurrentProgress.CurrentLevelName = MapDefinition.LevelName_Credits;
				//OpenMap(MapDefinition.LevelName_Credits);
				return false;
			}
			else
			{
				LOG_DISPLAY(RuntimeExecutionLog, "Count to next Level")
				CurrentProgress.CurrentLevel = currentValue;
			}
		}
		else
		{
			LOG_DISPLAY(RuntimeExecutionLog, "Count to next Dungeon")
			CurrentProgress.CurrentDungeon = currentValue;
			CurrentProgress.CurrentLevelName = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
		}
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Count to next Part")
		CurrentProgress.CurrentPart = (EPartInformation)currentValue;
	}
	return true;
}
