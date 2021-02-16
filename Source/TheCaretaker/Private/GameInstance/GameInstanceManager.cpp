/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "GameInstance/GameInstanceManager.h"

#include "TimerManager.h"

#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "SaveGame/TheCaretakerSaveGame.h"
#include "Widgets/Base/UserWidgetBase.h"
#include "Widgets/Ingame/IngameMenuUserWidget.h"
#include "Widgets/LevelSelect/LevelSelectionUserWidget.h"
#include "Widgets/Main/MainUI.h"
#include "Widgets/Menu/MainMenuWidget.h"
#include "Widgets/Monsters/MonsterInformationWidget.h"

UGameInstanceManager::UGameInstanceManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{	
	GameInformation = nullptr;

	SaveGameTemplate = nullptr;
	MainMenuTemplate = nullptr;
	MainSettingsTemplate = nullptr;
	LevelSelectorBlueprint = nullptr;
	MainUiTemplate = nullptr;
	IngameMenuTemplate = nullptr;
	MonsterInformationTemplate = nullptr;
	PowerUpInformationTable = nullptr;
	
	SaveGame = nullptr;
	MenuUI = nullptr;
	OptionsWidget = nullptr;
	LevelSelector = nullptr;
	MainUI = nullptr;
	IngameMenu = nullptr;
		
	SoundDefinition.ParameterSet.Add(FMODParameterSet(FName("MonsterAngry"), EFMODParameterType::FMOD_PT_MONSTER));
	SoundDefinition.ParameterSet.Add(FMODParameterSet(FName("Time"), EFMODParameterType::FMOD_PT_TIME));
	SoundDefinition.ParameterSet.Add(FMODParameterSet(FName("Trapped"), EFMODParameterType::FMOD_PT_TRAP));
	SoundDefinition.ParameterSet.Add(FMODParameterSet(FName("Heartbeat"), EFMODParameterType::FMOD_PT_HEARTBEAT));

	LevelChangeDelay = 3.0f;
	TimeToWaitForReloadMenu = 3.0f;

	PlayMode = EPlayMode::PM_CLASSIC;
	PlayModeExtraModifier = EPlayMode::PM_NONE;

	SecretUnlocked = FText::FromString("Secret Unlocked+");
	SecretUnlockedToEarlyTitle = FText::FromString("Secret Unlock too early+");
	SecretUnlockedToEarlyGrats = FText::FromString("Really good !+");
	SecretUnlockedToEarlyMessage = FText::FromString("You have not enought level points to unlock this secret.+");

	SecretUnlockedFailTitle = FText::FromString("No Secret Unlocked+");
	SecretUnlockedFailGrats = FText::FromString("Wrong Sentence !+");
	SecretUnlockedFailMessage = FText::FromString("Your input did not match any know slogan.+");

	MaxCountOfDifficulties = 9;

	ExtraLevelsDecryptKey = "f00_9asffS";
	CompetitionSecretIndex = 1;

	PlayPath = EPlayPath::PP_LINEAR;

	bAlreadyAddedExtraLevels = false;
	PickupSpawnLocations = TArray<FPickupSpawnLocation>();

	PowerUpInformationList = TArray<FPowerUpList>();

	bIsCaretakerOne = true;
}

void UGameInstanceManager::Init()
{
	Super::Init();

	PlayModeExtraModifier = EPlayMode::PM_NONE;

	LoadSaveGame();

	//SaveGame->AddSolvedSecretSloganIndex(0);
	SaveGame->AddSolvedSecretSloganIndex(1);

	LoadLevelInformation();

	TestExtraLevelsSetup();

	LoadPlayModeInformation();

	LoadPlayModeModifierInformation();

	LoadCredentialSetup();

	SetupSaveGameData();

	CalculateCurrentLevelPoints();

	RecalculateCurrentProgress();

	GetSavedPlayMode();

	if (PlayMode == EPlayMode::PM_NONE)
		PlayMode = EPlayMode::PM_CLASSIC;

	CheckHighScores();

	LoadPowerUpSetup();

	UE_LOG(LogTemp, Display, TEXT("Current Map Name: %s"), *CurrentProgress.CurrentLevelName.ToString());
	UE_LOG(LogTemp, Display, TEXT("Current Level: %d"), CurrentProgress.CurrentLevel);
	UE_LOG(LogTemp, Display, TEXT("Current Dungeon: %d"), CurrentProgress.CurrentDungeon);
	UE_LOG(LogTemp, Display, TEXT("Current Part: %d"), CurrentProgress.CurrentPart);
}

void UGameInstanceManager::GetSavedPlayMode()
{
	PlayMode = SaveGame->GetGamePlayMode();
}

bool UGameInstanceManager::IsPartTwoAchieved() const
{
	return IsPart2();
}

bool UGameInstanceManager::IsPartTwo() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find SaveGame. This shouldn't happen !")
		return false;
	}
	return SaveGame->bIsPart2;
}

const bool UGameInstanceManager::TestSetup() const
{
	bool IsOk = true;

	if (GameInformation == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInformation is null. Please set up GameInformation with a valid DataTable!");
		IsOk = false;
	}
	if (SecretCredentialList == nullptr)
	{
		LOG_WARNING(InitializationLog, "SecretCredentialList is null. Please set up SaveGameTemplate with a valid DataTable!");
		IsOk = false;
	}
	if (SaveGameTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGameTemplate is null. Please set up SaveGameTemplate with a valid DataTable!");
		IsOk = false;
	}
	if (PlayModeInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "PlayModeInformationTable is null. Please set up PlayModeInformationTable with a valid DataTable!");
		IsOk = false;
	}
	if (PlayModeModifierInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "PlayModeModifierInformationTable is null. Please set up PlayModeModifierInformationTable with a valid DataTable!");
		IsOk = false;
	}
	if (MainMenuTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Menu Blueprint was null in GameMode. Please set up MainMenuTemplate with a valid UserWidget");
		IsOk = false;
	}
	if (MainSettingsTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Options Menu Blueprint was null in GameMode. Please set up MainSettingsTemplate with a valid UserWidget");
		IsOk = false;
	}
	if (LevelSelectorBlueprint == nullptr)
	{
		LOG_WARNING(InitializationLog, "Menu Blueprint was null in GameMode. Please set up LevelSelectorBlueprint with a valid UserWidget");
		IsOk = false;
	}
	if (MainUiTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Options Menu Blueprint was null in GameMode. Please set up MainUiTemplate with a valid UserWidget");
		IsOk = false;
	}
	if (IngameMenuTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Menu Blueprint was null in GameMode. Please set up IngameMenuTemplate with a valid UserWidget");
		IsOk = false;
	}
	if (MonsterInformationTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Options Menu Blueprint was null in GameMode. Please set up MonsterInformationTemplate with a valid UserWidget");
		IsOk = false;
	}

	return IsOk;
}

void UGameInstanceManager::DoesSaveGameExist()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameName, 0))
	{
		if (SaveGameTemplate != nullptr)
		{
			USaveGame* SaveGameRaw = UGameplayStatics::CreateSaveGameObject(SaveGameTemplate);

			UGameplayStatics::SaveGameToSlot(SaveGameRaw, SaveGameName, 0);
			LOG_DISPLAY(InitializationLog, "SaveGame created!")
		}
		else
		{
			LOG_WARNING(InitializationLog, "Could not Save Game, because Blueprint Setup is missing a valid SaveGame")
			return;
		}
	}
	else
	{
		LOG_DISPLAY(InitializationLog, "SaveGame exists!")
	}
}



void UGameInstanceManager::LoadRawSaveGame()
{
	USaveGame* SaveGameRaw = UGameplayStatics::LoadGameFromSlot(SaveGameName, 0);

	if (SaveGameRaw == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find Load Game from Slot! This shouldn't happen !")
		return;
	}

	SaveGame = Cast<UTheCaretakerSaveGame>(SaveGameRaw);

	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast SaveGame to interface! This shouldn't happen !")
		return;
	}
}

void UGameInstanceManager::EmptyWidgets()
{
	if (MainUI != nullptr)
	{
		MainUI->RemoveFromParent();
		MainUI = nullptr;
	}

	if (IngameMenu != nullptr)
	{
		IngameMenu->RemoveFromParent();
		IngameMenu = nullptr;
	}

	if (MenuUI != nullptr)
	{
		MenuUI->RemoveFromParent();
		MenuUI = nullptr;
	}
	if (OptionsWidget != nullptr)
	{
		OptionsWidget->RemoveFromParent();
		OptionsWidget = nullptr;
	}
	if (LevelSelector != nullptr)
	{
		LevelSelector->RemoveFromParent();
		OptionsWidget = nullptr;
	}
}

bool UGameInstanceManager::CompletedCurrentLevel()
{
	bool ShowCredentials = true;
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not find SaveGame!")
	}
	else
	{
		if (SaveGame->GetTutorialFinished((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode) == false)
			SaveGame->SetTutorialFinished((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, true);

		if (CurrentProgress.CurrentDifficulty == -1)
		{
			CurrentProgress.SetCurrentDifficulty(0);
		}
		ShowCredentials = !SaveGame->CompletedCurrentLevel(
			PlayMode != EPlayMode::PM_HOPHOP ? PlayMode : TempPlayMode, 
			CurrentProgress.CurrentLevel, 
			CurrentProgress.CurrentDungeon, 
			!(CurrentProgress.CurrentPart <= 0) ? CurrentProgress.CurrentPart - 1 : 0,
			CurrentProgress.CurrentDifficulty);
		SaveGame->AddHeatPoints((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, CurrentProgress.CurrentDifficulty + 1);
		if (ShowCredentials == true)
		{
			FTimerHandle TimerHandle_SmallDelay;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_SmallDelay, this, &UGameInstanceManager::AchieveProgress, 1.5f, false);

		}
		SaveGameData();
	}

	CalculateCurrentLevelPoints();

	return ShowCredentials;
}

void UGameInstanceManager::CalculateCurrentLevelPoints()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog,"Could not find SaveGame")
	}
	else
	{
		CurrentProgress.CurrentLevelPoints = SaveGame->CalculateLevelPoints();
		UE_LOG(LogTemp, Display, TEXT("Earned Levelpoints: %d"), CurrentProgress.CurrentLevelPoints);
	}
}

void UGameInstanceManager::RecalculateCurrentProgress()
{
	CalculateCurrentDifficulty();

	CurrentProgress = SaveGame->GetCurrentProgress();
	if (CurrentProgress.CurrentPart == 0)
		CurrentProgress.SetCurrentPart(EPartInformation::EPI_LEVEL1);
	CurrentProgress.CurrentLevelName = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
}

void UGameInstanceManager::UpdateCurrentProgress()
{
	if (SaveGame == nullptr)
	{
		CurrentProgress.CurrentDifficulty = 0;
	}
	else
	{
		for (auto PlayModeInfo : PlayModeInformation)
		{
			if (PlayModeInfo.PlayMode == PlayMode)
			{
				if (CurrentProgress.CurrentLevel >= PlayModeInfo.Levels.Num())
				{
					continue;
				}

				if (SaveGame->CalculateCurrentDifficultyForPart((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentPart - 1) >= PlayModeInfo.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num())
				{
					CurrentProgress.CurrentDifficulty = PlayModeInfo.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num() - 1;
				}
				else
				{
					CurrentProgress.CurrentDifficulty = SaveGame->CalculateCurrentDifficultyForPart((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentPart - 1);
				}
			}
		}
	}
}

void UGameInstanceManager::AchieveProgress()
{
	CountAchievement(EAchievementType::AT_PROGRESS);
}

void UGameInstanceManager::LoadSaveGame()
{	
	DoesSaveGameExist();
		
	LoadRawSaveGame();
	
	SaveGame->CheckDefinitionSetup();	

	LOG_DISPLAY(InitializationLog, "Loading complete")
}

void UGameInstanceManager::SetupSaveGameData()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null !")
	}
	else
	{		
		SaveGame->SetupPlayModeInformationForLevels(PlayModeInformation);
	}
	
	//SaveGameData();
}

void UGameInstanceManager::DumpSaveGame()
{
	// DoesSaveGameExist();

	//LoadRawSaveGame();
	SaveGame->SetGamePlayMode(PlayMode);
	SaveGame->SetCurrentProgress(CurrentProgress);
	//SaveGame->AchievementLoadIdentifier.LatesMapNameAchieved = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
	//SaveGame->AchievementLoadIdentifier.MaxLevelAchieved = CurrentProgress.CurrentLevel;
	//SaveGame->AchievementLoadIdentifier.MaxDungeonAchieved = CurrentProgress.CurrentDungeon;
	//SaveGame->AchievementLoadIdentifier.MaxPartAchievedInDungeon = CurrentProgress.CurrentPart;

	UGameplayStatics::SaveGameToSlot(SaveGame, SaveGameName, 0);

	LOG_DISPLAY(InitializationLog, "Saving files complete")
}

FSpawnMarkerWidgetInformation::FSpawnMarkerWidgetInformation(AActor* ThisActor, UTexture2D* ThisTexture, bool IsMonster)
{
	bIsMonster = IsMonster;
	Actor = ThisActor;
	Texture = ThisTexture;
}
FSpawnMarkerWidgetInformation::FSpawnMarkerWidgetInformation()
{
	bIsMonster = false;
	Actor = nullptr;
	Texture = nullptr;
}