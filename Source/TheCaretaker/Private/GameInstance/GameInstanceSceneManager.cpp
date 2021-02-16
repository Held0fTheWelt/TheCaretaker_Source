/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameInstance/GameInstanceManager.h"

#include "TimerManager.h"

#include "Interfaces/GameAnalytics/GameAnalyticsInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "GameModes/Menu/GameMode_Menu.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Interfaces/GameMode/Menu/MenuGameModeInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "SaveGame/TheCaretakerSaveGame.h"
#include "States/Game/CaretakerGameState.h"
#include "Widgets/Ingame/IngameMenuUserWidget.h"
#include "Widgets/Main/MainUI.h"

int32 UGameInstanceManager::GetCurrentLevelPoints() const
{
	return SaveGame->CalculateLevelPoints();
}

void UGameInstanceManager::NewGame()
{

	FAchievementLoadIdentifier LoadIdentifier = SaveGame->GetLoadIdentifier(LevelInformation);
	
	CurrentProgress.CurrentLevel = LoadIdentifier.MaxLevelAchieved;
	CurrentProgress.CurrentDungeon = LoadIdentifier.MaxDungeonAchieved;
	CurrentProgress.CurrentPart = EPartInformation(LoadIdentifier.MaxPartAchievedInDungeon + 1);
	
	
	if (CurrentProgress.CurrentPart == EPartInformation::EPI_END)
	{
		CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL1;
		CurrentProgress.CurrentDungeon = CurrentProgress.CurrentDungeon + 1;
		if (CurrentProgress.CurrentDungeon >= LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel.Num())
		{
			CurrentProgress.CurrentDungeon = 0;
			//UpdateCurrentProgress();
			CurrentProgress.CurrentLevel = CurrentProgress.CurrentLevel + 1;

			if (CurrentProgress.CurrentLevel >= LevelInformation.Num())
			{
				if (SaveGame == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
				}
				else
				{
					if (SaveGame->bIsPart2 == false)
					{
						CurrentProgress.CurrentLevel = LevelInformation.Num() - 1;
						CurrentProgress.CurrentDungeon = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() - 1;
						CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL3;
					}
				}
			}
		}
	}

	CurrentProgress.CurrentLevelName = LoadIdentifier.LatesMapNameAchieved;
	
	FString fstringVar = CurrentProgress.CurrentLevelName.ToString();
	UE_LOG(LogTemp, Display, TEXT("LoadIdentifier loaded. %s"), *fstringVar);	


	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
		CurrentProgress.CurrentDifficulty = 0;
	}
	else
	{
		if (SaveGame->bIsPart2 == true)
		{
			if (CurrentProgress.CurrentLevel >= LevelInformation.Num())
			{
				CurrentProgress.SetCurrentLevel(0);
				CurrentProgress.SetCurrentDungeon(0);
				CurrentProgress.SetCurrentPart(EPartInformation::EPI_LEVEL1);
				CurrentProgress.SetCurrentLevelName(LevelInformation[0].DungeonsInLevel[0].MapNameOfPart);
			}

			CurrentProgress.CurrentDifficulty = CalculateCurrentDifficultyForPart(CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentPart - 1);

			for (auto PlayModeInfo : PlayModeInformation)
			{
				if (PlayModeInfo.PlayMode == ((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode))
				{
					if (CurrentProgress.CurrentDifficulty >= PlayModeInfo.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num())
					{						
						UE_LOG(LogTemp, Warning, TEXT("Current PlayMode: %d - CurrentDifficulty: %d"), PlayModeInfo.PlayMode, CurrentProgress.CurrentDifficulty);
						CurrentProgress.CurrentLevel = PlayModeInfo.Levels.Num() - 1;;
						CurrentProgress.CurrentDungeon = PlayModeInfo.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() - 1;
						CurrentProgress.CurrentDifficulty = PlayModeInfo.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num() - 1;
						CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL3;						
						CurrentProgress.CurrentLevelName = MapDefinition.LevelName_Credits;
					}
					else
					{
						/*if (SaveGame->HasPartAchieved(PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentDifficulty - 1, CurrentProgress.CurrentPart - 1) == false)
						{
							CurrentProgress.CurrentDifficulty = CurrentProgress.CurrentDifficulty - 1;
						}*/

						if (CurrentProgress.CurrentDifficulty == -1)
						{
							CurrentProgress.CurrentDifficulty = 0;
						}

						//if (CurrentProgress.CurrentDifficulty == 0 && SaveGame->HasPartAchieved(PlayMode, CurrentProgress.CurrentLevel, 2, 0, 2))
						//{
						//	CurrentProgress.CurrentDifficulty++;
						//}

						CurrentProgress.CurrentLevelName = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
					}
				}
			}
		}
		else
		{
			CurrentProgress.CurrentDifficulty = 0;
		}
	}
	
	UE_LOG(LogTemp, Display, TEXT("--------------------"));
	UE_LOG(LogTemp, Display, TEXT("Current Level: %d"), CurrentProgress.CurrentLevel);
	UE_LOG(LogTemp, Display, TEXT("Current Dungeon: %d"), CurrentProgress.CurrentDungeon);
	UE_LOG(LogTemp, Display, TEXT("Current Difficulty: %d"), CurrentProgress.CurrentDifficulty);
	UE_LOG(LogTemp, Display, TEXT("Current Part: %d"), CurrentProgress.CurrentPart);
	UE_LOG(LogTemp, Display, TEXT("--------------------"));
	ShowLoadLevel();
}

void UGameInstanceManager::ShowLoadLevel()
{
	IGameStateInterface* GameState = GetGameState();
	if (GameState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Restart Level, because GameState was null. This shouldn't happen !")	
	}
	else
	{
		GameState->StopCredentialTimer();
	}

	if (GetTimerManager().IsTimerActive(TimerHandle_LevelChangeDelay))
	{
		GetTimerManager().ClearTimer(TimerHandle_LevelChangeDelay);
	}

	if (GetTimerManager().IsTimerActive(TimerHandle_ReloadMenu))
	{
		GetTimerManager().ClearTimer(TimerHandle_ReloadMenu);
	}	

	EmptyWidgets();

	if (CurrentProgress.CurrentLevelName != EName::NAME_None)
	{
		UGameplayStatics::OpenLevel(GetWorld(), MapDefinition.LevelName_Load, true);
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Loading Level Name must be set to load level!");
	}
	SetMouseEvents(false);
}

void UGameInstanceManager::LoadLevelFinished()
{
	if (CurrentProgress.CurrentLevelName != EName::NAME_None)
	{
		UGameplayStatics::OpenLevel(GetWorld(), CurrentProgress.CurrentLevelName, true);
	}
	else
	{
		LOG_WARNING(RuntimeLog, "Current Level Name must be set to load level!");
	}
}

void UGameInstanceManager::RestartLevel()
{
	IGameStateInterface* GameState = GetGameState();
	if (GameState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Restart Level, because GameState was null. This shouldn't happen !")
		return;
	}

	if (LevelInformation.Num() > GameState->GetCurrentLevel())
	{
		if (LevelInformation[GameState->GetCurrentLevel()].DungeonsInLevel.Num() > GameState->GetCurrentDungeon())
		{
			ShowLoadLevel();
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not Load Dungeon, because not enough Dungeons in Level of GameInformation")
		}
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Load Dungeon, because not enough Levels in GameInformation")
	}
}

void UGameInstanceManager::OpenIngameMenu(EIngameMenuCall MenuCall)
{
	if (IngameMenu == nullptr)
	{
		if (IngameMenuTemplate == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not add IngameMenu, because Template was null ! Look up in your GameInstance Blueprint Settings")
		}
		else
		{
			// Create the widget and store it.
			IngameMenu = CreateWidget<UIngameMenuUserWidget>(this, IngameMenuTemplate);

			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());

			IMenuGameModeInterface* MenuGameMode = Cast<IMenuGameModeInterface>(GameMode);

			if (MenuGameMode != nullptr)
			{
				LOG_DISPLAY(RuntimeExecutionLog, "Don't opening Ingame Menu in Main Menu")
				return;
			}

			// now you can use the widget directly since you have a referance for it.
			// Extra check to  make sure the pointer holds the widget.
			if (MainUI)
			{
				switch (MenuCall)
				{
				case IMC_NONE:
					break;
				case IMC_DEFAULT:
					IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_PAUSE));
					IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_PAUSE));
					IngameMenu->IngameMenuCall();
					break;
				case IMC_DEATHBYSPIDER:
					IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_DEATH));
					IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_DEATH_SPD));
					IngameMenu->VictoryButton(false);
					break;
				case IMC_DEATHBYMONSTER:
					IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_DEATH));
					IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_DEATH_NSE));
					IngameMenu->VictoryButton(false);
					break;
				case IMC_DEATHBYTRAP:
					IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_DEATH));
					IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_DEATH_TRP));
					IngameMenu->VictoryButton(false);
					break;
				case IMC_TIME:
					 IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_DEATH));
					 IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_DEATH_TME));
					 IngameMenu->VictoryButton(false);
					break;
				case IMC_VICTORY:
					IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_VICTORY));
					IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_VICTORY));					
					IngameMenu->VictoryButton(true);
					break;
				case IMC_DEATHBYPICKUP:
					IngameMenu->Title->SetText(Messages.GetTextForMessageType(EGameMessageType::GMT_TITLE_DEATH));
					IngameMenu->Subtitle->SetTextNotification(Messages.GetTextForMessageType(EGameMessageType::GMT_SUB_DEATH_PWR));					
					IngameMenu->VictoryButton(false);
					break;
				default:
					break;
				}

				//let add it to the view port
				IngameMenu->AddToViewport();

				SetMouseEvents(true);
			}
			else
			{
				LOG_WARNING(RuntimeExecutionLog, "Creation of IngameMenu UI failed ! This shouldn't happen !");
			}

			SetPauseMode(true);
		}
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not add IngameMenu, because it already should exist !")
	}
}

void UGameInstanceManager::CloseIngameMenu()
{
	if (IngameMenu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not close IngameMenu, because it does not exist !")
	}
	else
	{
		SetMouseEvents(false);

		IngameMenu->RemoveFromParent();		
		IngameMenu = nullptr;

		SetPauseMode(false);
	}
}

void UGameInstanceManager::SaveGameData()
{
	LOG_DEFAULT(ShutdownLog, "Saving Game!");
	DumpSaveGame();
}

void UGameInstanceManager::Quit()
{
	LOG_DEFAULT(ShutdownLog, "Saving Game!");
	DumpSaveGame();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UGameAnalyticsInterface::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		IGameAnalyticsInterface* GameAnalytics = Cast<IGameAnalyticsInterface>(Actors[0]);
		if (GameAnalytics != nullptr)
		{
			GameAnalytics->StopGameAnalyicisSession();
		}
	}

	LOG_DEFAULT(ShutdownLog, "Quitting Game!");
	FGenericPlatformMisc::RequestExit(true);
}

void UGameInstanceManager::PlayYvesAgain()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Yves"), true);
}

void UGameInstanceManager::Reboot()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Map_Start"), true);
}

void UGameInstanceManager::Update(int32 UpdateState)
{

}

void UGameInstanceManager::OpenMap(FName &MapName)
{
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
}

AGameMode_Menu* UGameInstanceManager::GetMenuGameMode() 
{
	return Cast<AGameMode_Menu>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UGameInstanceManager::OpenMenuMap()
{
	OpenMap(MapDefinition.LevelName_Menu);
}

void UGameInstanceManager::PerformLevelChangeDelay()
{
	EmptyWidgets();

	//OpenMap(CurrentProgress.CurrentLevelName);
	ShowLoadLevel();
}


