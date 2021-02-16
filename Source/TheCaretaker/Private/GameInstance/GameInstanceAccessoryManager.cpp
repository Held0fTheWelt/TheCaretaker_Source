/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameInstance/GameInstanceManager.h"

#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/World.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/Monsters/Feeding/MonsterFeedingInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Game/CaretakerGameState.h"
#include "Structs/Achievement/Achievement.h"
#include "Structs/Achievement/AchievementDefinition.h"
#include "Structs/FMOD/FMODParameterSetList.h"
#include "Structs/Level/LevelSetup.h"
#include "Structs/PowerUp/PowerUpList.h"
#include "Structs/Secret/SecretSloganList.h"
#include "SaveGame/TheCaretakerSaveGame.h"

bool UGameInstanceManager::IsPowerUpAvailable(TSubclassOf<class APowerUp> PowerUp) const
{
	if (PowerUpInformationList.Num() == 0)
	{
		return false;
	}

	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null ! This shouldn't happen !")
		return false;
	}

	for (auto Element : PowerUpInformationList)
	{
		if (Element.PowerUp == PowerUp)
		{
			if (SaveGame->IsSecretSolved(Element.SecretSloganIndexBounding))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	LOG_WARNING(InitializationLog, "Could not find PowerUp Values !")

	return false;
}

bool UGameInstanceManager::IsCaretakerOne() const
{
	return bIsCaretakerOne;
}

bool UGameInstanceManager::HasPickupSpawnLocation(FName PickupName) const
{
	if (PickupSpawnLocations.Num() == 0)
		return false;

	IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameStateInterface was null ! This shouldn't happen !")
		return false;
	}
	else
	{
		int32 Level = GameStateInterface->GetCurrentLevel();
		int32 Dungeon = GameStateInterface->GetCurrentDungeon();
		int32 Part = GameStateInterface->GetCurrentPart();
		for (auto Pickup : PickupSpawnLocations)
		{
			if (Pickup.Level == Level
				&& Pickup.Dungeon == Dungeon
				&& Pickup.Part == Part
				&& Pickup.PickupName.IsEqual(PickupName))
			{
				return true;
			}
		}
	}

	return false;
}

FVector UGameInstanceManager::GetSpawnLocation(FName PickupName) const
{
	if (PickupSpawnLocations.Num() == 0)
		return FVector();

	IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameStateInterface was null ! This shouldn't happen !")
			return FVector();
	}
	else
	{
		int32 Level = GameStateInterface->GetCurrentLevel();
		int32 Dungeon = GameStateInterface->GetCurrentDungeon();
		int32 Part = GameStateInterface->GetCurrentPart();
		for (auto Pickup : PickupSpawnLocations)
		{
			if (Pickup.Level == Level
				&& Pickup.Dungeon == Dungeon
				&& Pickup.Part == Part
				&& Pickup.PickupName.IsEqual(PickupName))
			{
				return Pickup.SpawnLocation;
			}
		}
	}

	return FVector();
}

void UGameInstanceManager::SetSpawnLocation(FName PickupName, FVector SpawnLocation)
{
	IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameStateInterface was null ! This shouldn't happen !")
		return;
	}
	else
	{
		int32 Level = GameStateInterface->GetCurrentLevel();
		int32 Dungeon = GameStateInterface->GetCurrentDungeon();
		int32 Part = GameStateInterface->GetCurrentPart();
		
		if (!HasPickupSpawnLocation(PickupName))
		{
			FPickupSpawnLocation NewSpawnLocation = FPickupSpawnLocation();
			NewSpawnLocation.PickupName = PickupName;
			NewSpawnLocation.Level = Level;
			NewSpawnLocation.Dungeon = Dungeon;
			NewSpawnLocation.Part = Part;
			NewSpawnLocation.SpawnLocation = SpawnLocation;
		}
		else
		{
			for (int32 i = 0; i < PickupSpawnLocations.Num(); i++)
			{
				if (PickupSpawnLocations[i].Level == Level
					&& PickupSpawnLocations[i].Dungeon == Dungeon
					&& PickupSpawnLocations[i].Part == Part
					&& PickupSpawnLocations[i].PickupName.IsEqual(PickupName))
				{
					PickupSpawnLocations[i].SpawnLocation = SpawnLocation;
					return;
				}
			}
		}		
	}
}

TArray<float> UGameInstanceManager::GetFinalMonsterHungerAverages() const
{
	TArray<float> FinalHungers = TArray<float>();

	TArray<AActor*> Monsters;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMonsterFeedingInterface::StaticClass(), Monsters);

	for (auto MonsterActor : Monsters)
	{
		IMonsterFeedingInterface* Monster = Cast<IMonsterFeedingInterface>(MonsterActor);
		if (Monster == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast MonsterHunger to Interface. This shouldn't happen!")
		}
		else
		{
			FinalHungers.Add(Monster->CalculateFinalAverageHunger());
		}
	}

	return FinalHungers;
}

EPlayPath UGameInstanceManager::GetCurrentPlayPath() const
{
	return PlayPath;
}



int32 UGameInstanceManager::GetCurrentHeatPoints() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null ! This shouldn't happen !")
		return 0;
	}
		
	return SaveGame->GetCurrentHeatPoints();
}

EPlayMode UGameInstanceManager::GetCurrentPreferredPlayMode() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null ! This shouldn't happen !")
		return EPlayMode::PM_NONE;
	}

	return SaveGame->HasMostPlayedThisPlayMode();
}

bool UGameInstanceManager::IsCompeteAccessible() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame is null. Cannot check competition mode")
		return false;
	}

	TArray<int32> KnownSecretIndices = SaveGame->GetSolvedSecretSloganIndices();

	for (auto Index : KnownSecretIndices)
	{
		if (Index == CompetitionSecretIndex)
		{
			return true;
		}
	}

	return false;
}

TArray<TArray<TArray<FSecretCredential>>> UGameInstanceManager::GetKnownSecretCredentialsByArrays(int32 CurrentLevel) const
{
	TArray<TArray<TArray<FSecretCredential>>> ReturnValue = TArray<TArray<TArray<FSecretCredential>>>();
	
	FAchievementLoadIdentifier LoadIdentifier = SaveGame->GetLoadIdentifier(LevelInformation);

	for (int32 i = 0; i < 9; i++)
	{
		ReturnValue.Add(TArray<TArray<FSecretCredential>>());
	}

	FPlayModeInformation CurrentPlayModeInformation = FPlayModeInformation();

	for (auto PlayModeInfo : PlayModeInformation)
	{
		if (PlayModeInfo.PlayMode == PlayMode)
		{
			CurrentPlayModeInformation = PlayModeInfo;
			break;
		}
	}

	if (CurrentPlayModeInformation.Levels.Num() <= CurrentLevel)
	{
		LOG_WARNING(RuntimeExecutionLog, "CurrentLevelIndex exceeds values of levels")
	}
	else
	{
		FLevelSetup Levels = CurrentPlayModeInformation.Levels[CurrentLevel];

		for (int32 i = 0; i < Levels.DungeonsInLevel.Num(); i++)
		{
			for (int32 j = 0; j < Levels.DungeonsInLevel[i].Difficulties.Num(); j++)
			{
				for (int32 k = 0; k < Levels.DungeonsInLevel[i].Difficulties[j].DungeonParts.Num(); k++)
				{
					if (SaveGame->HasPartAchieved(PlayMode, CurrentLevel, i, j, k))
					{
						if (ReturnValue[i * 3 + k].Num() <= j)
						{
							ReturnValue[i * 3 + k].Add(TArray<FSecretCredential>());
						}

						if (j >= Levels.DungeonsInLevel[i].Difficulties.Num())
						{
							continue;
						}

						if (k >= Levels.DungeonsInLevel[i].Difficulties[j].DungeonParts.Num())
						{
							continue;
						}

						ReturnValue[i * 3 + k][j].Add(Levels.DungeonsInLevel[i].Difficulties[j].DungeonParts[k].PartsWithDifficulty[0].SecretCredentials[0]);
						ReturnValue[i * 3 + k][j].Add(Levels.DungeonsInLevel[i].Difficulties[j].DungeonParts[k].PartsWithDifficulty[0].SecretCredentials[1]);
					}
				}
			}
		}
	}

	return ReturnValue;
}

TArray<int32> UGameInstanceManager::GetCurrentSolvedSloganIndices() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
		return TArray<int32>();
	}

	TArray<int32> CurrentIndices = SaveGame->GetSolvedSecretSloganIndices();
	TArray<int32> ReturnValue = TArray<int32>();

	for (auto SecretSlogan : SecretSlogans.Slogans)
	{
		for (auto Index : CurrentIndices)
		{
			if (Index == SecretSlogan.SloganIndex && PlayMode == SecretSlogan.Episode)
			{
				ReturnValue.Add(Index);
			}
		}
	}

	return ReturnValue;
}

TArray<int32> UGameInstanceManager::GetSolvedSloganIndices() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"SaveGame was null ! This shouldn't happen !")
		return TArray<int32>();
	}

	return SaveGame->GetSolvedSecretSloganIndices();
}

TArray<FString> UGameInstanceManager::GetSecretSlogans() const
{	
	return SecretSlogans.GetSecretSlogans(PlayMode);
}

bool UGameInstanceManager::CompetitionAvailable() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
		return false;
	}

	TArray<int32> CurrentIndices = SaveGame->GetSolvedSecretSloganIndices();

	for (auto Index : CurrentIndices)
	{
		if (Index == 1)
		{
			return true;
		}
	}

	return false;
}

bool UGameInstanceManager::HasTutorialFinished() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null! This shouldn't happen!")
		return false;
	}
	else
	{
		return SaveGame->GetTutorialFinished(PlayMode);
	}
}

bool UGameInstanceManager::HasPartAchieved(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null! This shouldn't happen!")
		return false;
	}
	else
	{
		return SaveGame->HasPartAchieved((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, Level, Dungeon, Difficulty, Part);
	}
}

int32 UGameInstanceManager::CalculateCurrentDifficultyForPart(int32 Level, int32 Dungeon, int32 Part)
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null! This shouldn't happen!")
		return 0;
	}
	else
	{
		if (SaveGame->bIsPart2)
		{
			return SaveGame->CalculateCurrentDifficultyForPart((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, Level, Dungeon, Part);
		}
		else
		{
			return 0;
		}
	}
}

int32 UGameInstanceManager::GetMaxDifficulties(int32 Level, int32 Dungeon) const
{
	for (auto PlayModeInfo : PlayModeInformation)
	{
		if (PlayModeInfo.PlayMode == ((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode))
		{
			return PlayModeInfo.Levels[Level].DungeonsInLevel[Dungeon].Difficulties.Num();
		}
	}
	return 0;
}

int32 UGameInstanceManager::GetSpiderPathNumber(EPartInformation CurrentPart) const
{
	
	return int32();
}



int32 UGameInstanceManager::CalculateCurrentDifficulty()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null! This shouldn't happen!")
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Here %d levels"), LevelInformation.Num());

		int32 Result = SaveGame->GetLoadIdentifier(LevelInformation).MaxDifficultyAchieved;
		UE_LOG(LogTemp, Display, TEXT("Difficulty now is: %d"), Result);
		return Result;
	}
	return 0;
}

void UGameInstanceManager::CountBeforeBackToMenu()
{
	CountCurrentProgress();
	LOG_DISPLAY(RuntimeExecutionLog, "Progress Counted. Returning to Menu")
	SaveGameData();
}

void UGameInstanceManager::TutorialFinished()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
	}
	else
	{
		SaveGame->SetTutorialFinished(PlayMode, true);
	}
}



void UGameInstanceManager::SetCurrentDifficulty(int32 Difficulty)
{
	CurrentProgress.SetCurrentDifficulty(Difficulty);
}

void UGameInstanceManager::UpdateGameStateValues()
{
	if (GetGameState() != nullptr)
	{
		GetGameState()->SetCurrentLevel(CurrentProgress.CurrentLevel);
		GetGameState()->SetCurrentDungeon(CurrentProgress.CurrentDungeon);
		GetGameState()->SetCurrentPart(CurrentProgress.CurrentPart);
	}

	UE_LOG(LogTemp, Display, TEXT("Current Progress"));
	UE_LOG(LogTemp, Display, TEXT("PlayMode: %d"), PlayMode);
	UE_LOG(LogTemp, Display, TEXT("Current Level: %d"), CurrentProgress.CurrentLevel);
	UE_LOG(LogTemp, Display, TEXT("Current Dungeon: %d"), CurrentProgress.CurrentDungeon);
	UE_LOG(LogTemp, Display, TEXT("Current Difficulty: %d"), CurrentProgress.CurrentDifficulty);
	UE_LOG(LogTemp, Display, TEXT("Current Part: %d"), CurrentProgress.CurrentPart);
	UE_LOG(LogTemp, Display, TEXT("Current LevelPoints: %d"), GetCurrentLevelPoints());
}

void UGameInstanceManager::ResetPlayModes()
{
	if (PlayMode == EPlayMode::PM_NONE || PlayMode == EPlayMode::PM_HOPHOP || PlayMode == EPlayMode::PM_TEST)
	{
		if (TempPlayMode == EPlayMode::PM_NONE)
			TempPlayMode = EPlayMode::PM_CLASSIC;
		PlayMode = TempPlayMode;
	}

	SaveGame->SetGamePlayMode(PlayMode);
	SaveGameData();
}

bool UGameInstanceManager::IsPart2() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find SaveGame ! This shouldn't happen !")
		return false;
	}
	else
	{
		return SaveGame->bIsPart2;
	}
}

TArray<FAchievementDefinition> UGameInstanceManager::GetAchievements()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not get Achievements, because SaveGame was null. This shouldn't happen !")
		return TArray<FAchievementDefinition>();
	}

	UDataTable* DataTable = SaveGame->GetAchievementDefinitions();

	if (DataTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not get Achievements, because DataTable was missing in SaveGame. This shouldn't happen !")
		return TArray<FAchievementDefinition>();
	}

	static const FString ContextString(TEXT("AchievementDefinitionTable"));

	TArray<FName> RowNames = DataTable->GetRowNames();
	TArray<FAchievementDefinition> Achievements = TArray<FAchievementDefinition>();
	for (int32 i = 0; i < RowNames.Num(); i++)
	{
		FAchievementDefinition* RankDefinition = DataTable->FindRow<FAchievementDefinition >(RowNames[i], ContextString, true);
		Achievements.Add(*RankDefinition);
	}
	
	return Achievements;
}

FMODParameterSet UGameInstanceManager::GetFMODParameterSet(EFMODParameterType ParameterType)
{
	for (auto ParameterSet : SoundDefinition.ParameterSet)
	{
		if (ParameterSet.ParameterType == ParameterType)
		{
			return ParameterSet;
		}
	}
	return FMODParameterSet(EName::NAME_None, EFMODParameterType::FMOD_PT_NONE, 0);
}


bool UGameInstanceManager::ShouldWaitForEndOfTime() const
{
	TArray<FLevelSetup> LevelSetup;
	for (auto PlayModeInfo : PlayModeInformation)
	{
		if (PlayModeInfo.PlayMode == PlayMode)
		{
			LevelSetup = PlayModeInfo.Levels;
		}
	}

	if (LevelSetup.Num() == 0)
	{
		return false;
	}
	else
	{
		if(CurrentProgress.CurrentPart == 0)
		{
			return LevelSetup[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[0].DungeonParts[CurrentProgress.CurrentPart].PartsWithDifficulty[0].bWaitForEndOfTime;
		}
		else
		{
			return LevelSetup[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[CurrentProgress.CurrentPart - 1].PartsWithDifficulty[0].bWaitForEndOfTime;
		}
	}
}



void UGameInstanceManager::SetCurrentDungeonPartInfos(int32 NewCurrentLevel, int32 NewCurrentDungeon, TEnumAsByte<EPartInformation> NewCurrentPart)
{
	CurrentProgress.SetCurrentLevel(NewCurrentLevel);
	CurrentProgress.SetCurrentDungeon(NewCurrentDungeon);
	CurrentProgress.SetCurrentPart(NewCurrentPart);

	CurrentProgress.SetCurrentLevelName(LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart);

	IGameStateInterface* GameState = GetGameState();

	if (GameState != nullptr)
	{
		GameState->UpdateCurrentInfos(CurrentProgress);
	}
}

TArray<FLevelInformation> UGameInstanceManager::GetLevelInformation() const
{
	return LevelInformation;
}

void UGameInstanceManager::SetMouseEvents(bool On)
{
	APlayerController* Current = GetFirstLocalPlayerController();
	if (Current == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not find PlayerController! This shouldn't happen!")
		return;
	}

	if (On)
	{
		Current->bShowMouseCursor = true;
		Current->bEnableClickEvents = true;
		Current->bEnableMouseOverEvents = true;
	}
	else
	{
		Current->bShowMouseCursor = false;
		Current->bEnableClickEvents = false;
		Current->bEnableMouseOverEvents = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(Current);
	}
}

FAchievementLoadIdentifier UGameInstanceManager::GetLoadIdentifier() 
{
	// In case of Scene Change
	//LoadSaveGame();

	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null!")
		return FAchievementLoadIdentifier();
	}
	return SaveGame->GetLoadIdentifier(LevelInformation);
}

TArray<FAchieved> UGameInstanceManager::GetAchievedRewards()
{
	// In case of Scene Change
	//LoadSaveGame();

	if (SaveGame == nullptr)
	{
		return TArray<FAchieved>();
	}

	return SaveGame->GetAchievedRewards();
}

UMainUI* UGameInstanceManager::GetGameUI()
{
	return MainUI;
}

IGameStateInterface* UGameInstanceManager::GetGameState()
{
	return Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));
}

TArray<FLevelInformation> UGameInstanceManager::GetGameInformation() const
{
	return LevelInformation;
}

FName UGameInstanceManager::GetMenuLevelName() const
{
	return MapDefinition.LevelName_Menu;
}

FName UGameInstanceManager::GetTutorialLevelName() const
{
	return MapDefinition.LevelName_Tutorial;
}

void UGameInstanceManager::SetCurrentLevelName(FName NewLevelName)
{
	CurrentProgress.CurrentLevelName = NewLevelName;
}

FName UGameInstanceManager::GetCurrentLevelName() const
{
	return CurrentProgress.CurrentLevelName;
}

int32 UGameInstanceManager::GetCurrentLevel() const
{
	return CurrentProgress.CurrentLevel;
}

int32 UGameInstanceManager::GetCurrentDungeon() const
{
	return CurrentProgress.CurrentDungeon;
}

int32 UGameInstanceManager::GetCurrentDifficulty() const
{
	return CurrentProgress.CurrentDifficulty;
}

EPartInformation UGameInstanceManager::GetCurrentPart() const
{
	return CurrentProgress.CurrentPart;
}

bool UGameInstanceManager::GetPlayYvesOnce()
{
	// In case of Scene Change
	//LoadSaveGame();

	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find SaveGame. Returning false, not Playing Yves once.")
			return false;
	}

	return SaveGame->GetPlayYvesOnce();
}

void UGameInstanceManager::SetPlayYvesOnce(bool PlayedOnce)
{
	// In case of Scene Change
	//LoadSaveGame();

	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find SaveGame. Returning false, not setting value for Playing Yves once.")
			return;
	}

	SaveGame->SetPlayYvesOnce(PlayedOnce);
}

void UGameInstanceManager::SetLastLevelName()
{
	CurrentProgress.CurrentLevelName = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
	OpenMap(MapDefinition.LevelName_Menu);
}

FCurrentProgress UGameInstanceManager::GetCurrentProgress() const
{
	return CurrentProgress;
}

FName UGameInstanceManager::GetLevelName(int32 CurrentLevel, int32 CurrentDungeon)
{
	if(CurrentLevel >= LevelInformation.Num())
		return MapDefinition.LevelName_Credits;
	if(CurrentDungeon >= LevelInformation[CurrentLevel].DungeonsInLevel.Num())
		return MapDefinition.LevelName_Credits;

	return LevelInformation[CurrentLevel].DungeonsInLevel[CurrentDungeon].MapNameOfPart;
}


FPlayModeInformation UGameInstanceManager::GetPlayModeInformation(EPlayMode Mode) const
{
	for (auto PlayModeInfo : PlayModeInformation)
	{
		if (PlayModeInfo.PlayMode == Mode)
		{
			return PlayModeInfo;
		}
	}

	return FPlayModeInformation();
}

FPlayModeModifierInformation UGameInstanceManager::GetPlayModeModifierInformation(EPlayMode Mode) const
{
	for (auto ModeModifier : PlayModeModifiers)
	{
		if (ModeModifier.PlayMode == Mode)
		{
			return ModeModifier;
		}
	}

	return FPlayModeModifierInformation();
}

EPlayMode UGameInstanceManager::GetPlayMode() const
{
	return PlayMode;
}
TArray<float> UGameInstanceManager::GetSpiderPathSpreadValues(EPartInformation CurrentPart) const
{
	FPlayModeInformation Mode = GetPlayModeInformation(PlayMode);

	if (Mode.Levels.Num() <= CurrentProgress.CurrentLevel)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. CurrentLevel Value exceeds")
		return TArray<float>();
	}

	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() <= CurrentProgress.CurrentDungeon)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Dungeon Value exceeds")
		return TArray<float>();
	}
	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num() <= CurrentProgress.CurrentDifficulty)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Difficulty Value exceeds")
		return TArray<float>();
	}	

	FPartDifficultyInformation Info;

	if (CurrentPart == 0)
	{
		Info = Mode.Levels[CurrentProgress.CurrentLevel]
			.DungeonsInLevel[CurrentProgress.CurrentDungeon]
			.Difficulties[CurrentProgress.CurrentDifficulty]
			.DungeonParts[CurrentPart]
			.PartsWithDifficulty[CurrentPart];
	}
	else
	{
		Info = Mode.Levels[CurrentProgress.CurrentLevel]
			.DungeonsInLevel[CurrentProgress.CurrentDungeon]
			.Difficulties[CurrentProgress.CurrentDifficulty]
			.DungeonParts[CurrentPart - 1]
			.PartsWithDifficulty[CurrentPart - 1];
	}

	return Info.PathSpreadValue;
}

int32 UGameInstanceManager::GetNumberToSpawn(ESpawnPointType SpawnPointType, EPartInformation CurrentPart) 
{	
	FPlayModeInformation Mode = GetPlayModeInformation(PlayMode);

	if (Mode.Levels.Num() <= CurrentProgress.CurrentLevel)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. CurrentLevel Value exceeds")
		return 0;
	}

	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() <= CurrentProgress.CurrentDungeon)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Dungeon Value exceeds")
		return 0;
	}
	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num() <= CurrentProgress.CurrentDifficulty)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Difficulty Value exceeds")
			return 0;
	}
	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts.Num() <= GetGameState()->GetCurrentPart() - 1)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Part Value exceeds")
		UE_LOG(LogTemp, Warning, TEXT("%d"), GetGameState()->GetCurrentPart() - 1);
		return 0;
	}
	if (GetGameState()->GetCurrentPart() == 0)
	{
		if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart()].PartsWithDifficulty.Num() <= CurrentPart - 1)
		{
			LOG_WARNING(InitializationLog, "Setup is wrong. Loading Part Value exceeds")
				return 0;
		}
	}
	else
	{
		if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart() - 1].PartsWithDifficulty.Num() <= CurrentPart - 1)
		{
			LOG_WARNING(InitializationLog, "Setup is wrong. Loading Part Value exceeds")
				return 0;
		}
	}

	FPartDifficultyInformation Info;

	if (GetGameState()->GetCurrentPart() == 0)
	{
		Info = Mode.Levels[CurrentProgress.CurrentLevel]
											  .DungeonsInLevel[CurrentProgress.CurrentDungeon]
											  .Difficulties[CurrentProgress.CurrentDifficulty]
											  .DungeonParts[GetGameState()->GetCurrentPart()]
											  .PartsWithDifficulty[CurrentPart - 1];
	}
	else
	{
		Info = Mode.Levels[CurrentProgress.CurrentLevel]
			.DungeonsInLevel[CurrentProgress.CurrentDungeon]
			.Difficulties[CurrentProgress.CurrentDifficulty]
			.DungeonParts[GetGameState()->GetCurrentPart() - 1]
			.PartsWithDifficulty[CurrentPart - 1];
	}


	switch (SpawnPointType)
	{
	case SPT_NONE:
		break;
	case SPT_GARBAGE:
		return Info.NumberOfGarbage;
		break;
	case SPT_CHEST:
		return Info.NumberOfChests;
		break;
	case SPT_TRAP:
		return Info.NumberOfTraps;
		break;
	case SPT_VOLUME:
		break;
	case SPT_SPIDER:
		return Info.NumberOfSpiders;
		break;
	case SPT_SPIDERPATH:
		return Info.PathNumberMax;
		break;
	default:
		break;
	}

	return 0;
}

float UGameInstanceManager::GetTimeToGetHungry(EPartInformation CurrentPart)
{
	if (PlayMode == EPlayMode::PM_HOPHOP)
	{
		return 1;
	}
	

	FPlayModeInformation Mode = GetPlayModeInformation(PlayMode);

	if (Mode.Levels.Num() <= GetGameState()->GetCurrentLevel())
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. CurrentLevel Value exceeds")
		UE_LOG(LogTemp, Warning, TEXT("%d - %d"), Mode.Levels.Num(), GetGameState()->GetCurrentLevel());
		return 0;
	}

	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() <= CurrentProgress.CurrentDungeon)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Dungeon Value exceeds")
		return 0;
	}
	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num() <= CurrentProgress.CurrentDifficulty)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Difficulty Value exceeds")
		return 0;
	}
	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts.Num() <= GetGameState()->GetCurrentPart()-1)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Part Value exceeds")
		UE_LOG(LogTemp, Warning, TEXT("%d"), GetGameState()->GetCurrentPart()-1);
		return 0;
	}
	if (GetGameState()->GetCurrentPart() <= 0)
	{
		if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart()].PartsWithDifficulty.Num() <= CurrentPart - 1)
		{
			LOG_WARNING(InitializationLog, "Setup is wrong. Loading Part Value exceeds")
			return 0;
		}
	}
	else
	{
		if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart() - 1].PartsWithDifficulty.Num() <= CurrentPart - 1)
		{
			LOG_WARNING(InitializationLog, "Setup is wrong. Loading Part Value exceeds")
			return 0;
		}
	}

	FPartDifficultyInformation Info;

	if (GetGameState()->GetCurrentPart() <= 0)
	{
		if (CurrentPart == 0)
		{
			Info = Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart()].PartsWithDifficulty[CurrentPart];
		}
		else
		{
			Info = Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart()].PartsWithDifficulty[CurrentPart - 1];
		}
	}
	
	else
	{
		if (CurrentPart == 0)
		{
			Info = Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart() - 1].PartsWithDifficulty[CurrentPart];
		}
		else
		{
			Info = Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[GetGameState()->GetCurrentPart() - 1].PartsWithDifficulty[CurrentPart - 1];
		}
	}
	

	FPlayModeModifierInformation Modifier = GetPlayModeModifierInformation(Info.PlayMode);

	return Info.TimeToGetHungry * Modifier.TimeToGetHungryModifier;
}

FCharacterSetup UGameInstanceManager::GetCharacterSetup() const
{
	FPlayModeModifierInformation Modifier = GetPlayModeModifierInformation(PlayMode);	
	return Modifier.CharacterSetup;
}

FSpiderSetup UGameInstanceManager::GetSpiderSetup() const
{
	FPlayModeModifierInformation Modifier = GetPlayModeModifierInformation(PlayMode);
	return Modifier.SpiderSetup;
}

FClockSetup UGameInstanceManager::GetClockSetup() const
{
	FPlayModeModifierInformation Modifier = GetPlayModeModifierInformation(PlayMode);
	return Modifier.ClockModifier;
}

bool UGameInstanceManager::ConsoleInfoShown() const
{
	return SaveGame->bConsoleInfoShown;
}

void UGameInstanceManager::SetConsoleInfoShown(bool InfoShown)
{
	SaveGame->bConsoleInfoShown = InfoShown;
}

TArray<int32> UGameInstanceManager::GetKnownSecretSloganIndices() const
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
		return TArray<int32>();
	}
	else
	{
		return SaveGame->GetSolvedSecretSloganIndices();
	}
}
