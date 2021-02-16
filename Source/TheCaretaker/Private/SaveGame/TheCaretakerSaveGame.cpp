/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SaveGame/TheCaretakerSaveGame.h"

#include "Enums/Achievement/AchievementType.h"
#include "Structs/Achievement/Achievement.h"
#include "Engine/DataTable.h"
#include "Log/GlobalLog.h"

#pragma region Constructor
UTheCaretakerSaveGame::UTheCaretakerSaveGame()
{
	Achievements = TArray<FAchievement>();
	Achievements.Add(FAchievement(EAchievementType::AT_GARBAGE));
	Achievements.Add(FAchievement(EAchievementType::AT_GOLD));
	Achievements.Add(FAchievement(EAchievementType::AT_MEAT));
	Achievements.Add(FAchievement(EAchievementType::AT_TRAP));
	Achievements.Add(FAchievement(EAchievementType::AT_VICTORY));
	Achievements.Add(FAchievement(EAchievementType::AT_DEATHBYSPIDER));
	Achievements.Add(FAchievement(EAchievementType::AT_DEATHBYMONSTER));
	Achievements.Add(FAchievement(EAchievementType::AT_DEATHBYTRAP));
	Achievements.Add(FAchievement(EAchievementType::AT_DEATHBYPICKUP));
	Achievements.Add(FAchievement(EAchievementType::AT_PROGRESS));
	Achievements.Add(FAchievement(EAchievementType::AT_SECRETUNLOCKED));
	Achievements.Add(FAchievement(EAchievementType::AT_WINCONDITIONMET));
	Achievements.Add(FAchievement(EAchievementType::AT_PICKUP));
	Achievements.Add(FAchievement(EAchievementType::AT_BAD_PICKUP));

	bYvesPlayedOnce = true;

	GameSecrets = FGameSecrets();
	HeatHistory = FHeatHistory();

	bIsPart2 = false;
	bConsoleInfoShown = false;

	bTutorialFinished.Add(false);
	bTutorialFinished.Add(true);

	

	bExtraLevelsAchievementInformationAdded = false;

	CompleteHighScore = TArray<FHighScoreComplete>();
}
#pragma endregion

#pragma region Getter
TArray<FPlayModeSolveInformation> UTheCaretakerSaveGame::GetSolveInformationByPlayModes() const
{
	return SolveInformationByPlayModes;
}
FAchievementLoadIdentifier UTheCaretakerSaveGame::GetLoadIdentifier(TArray<FLevelInformation> LevelInformation)
{
	FAchievementLoadIdentifier AchievementLoadIdentifier = FAchievementLoadIdentifier();

	TArray<TArray<FDungeonPartSolveInformation>> TempLists = TArray<TArray<FDungeonPartSolveInformation>>();

	for (int32 i = 0; i < 9; i++)
	{
		TArray<FDungeonPartSolveInformation> List = TArray<FDungeonPartSolveInformation>();
		TempLists.Add(List);
	}

	for (auto SolveInformation : SolveInformationByPlayModes)
	{
		if (SolveInformation.PlayMode == GamePlayMode)
		{
			for (int i = 0; i < SolveInformation.LevelInformation.Num(); i++)
			{
				FLevelSolveInformation LevelSolveInformation = SolveInformation.LevelInformation[i];

				for (int j = 0; j < LevelSolveInformation.Dungeons.Num(); j++)
				{
					FDungeonSolveInformation DungeonSolveInformation = LevelSolveInformation.Dungeons[j];

					for (int k = 0; k < DungeonSolveInformation.Difficulties.Num(); k++)
					{
						FDungeonDifficultySolveInformation DifficultySolveInformation = DungeonSolveInformation.Difficulties[k];
						
						for (int l = 0; l < DifficultySolveInformation.DungeonParts.Num(); l++)
						{
							FDungeonPartSolveInformation DungeonPart = DifficultySolveInformation.DungeonParts[l];
							TempLists[k].Add(DungeonPart);
						}
					}
				}
			}
		}
	}

	int32 Level = 0;
	int32 Dungeon = 0;
	EPartInformation Part = EPartInformation::EPI_NONE;
	int32 Difficulty = 0;
	FName MapName = FName("");

	for (int i = 0; i < TempLists.Num(); i++)
	{
		TArray<FDungeonPartSolveInformation> List = TempLists[i];

		for (int j = 0; j < List.Num(); j++)
		{
			if (List[j].bFinished == false)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Failed on element %d, in list %d, difficulty is %d"), j, i, Difficulty);
				break;
			}
			else
			{
				Level = j / 9;
				Dungeon = j / 3;
				Part = (EPartInformation)((j % 3) + 1);
				Difficulty = i + 1;
			}
		}
	}

	if (Level > AchievementLoadIdentifier.MaxLevelAchieved)
	{
		AchievementLoadIdentifier.MaxLevelAchieved = Level;
	}
	if (Dungeon > AchievementLoadIdentifier.MaxDungeonAchieved)
	{
		AchievementLoadIdentifier.MaxDungeonAchieved = Dungeon;
		AchievementLoadIdentifier.LatesMapNameAchieved = LevelInformation[Level].DungeonsInLevel[Dungeon / LevelInformation.Num()].MapNameOfPart;
	}
	if (Part > AchievementLoadIdentifier.MaxPartAchievedInDungeon)
	{
		AchievementLoadIdentifier.MaxPartAchievedInDungeon = Part;
	}
	if (Difficulty > AchievementLoadIdentifier.MaxDifficultyAchieved)
	{
		AchievementLoadIdentifier.MaxDifficultyAchieved = Difficulty;
	}
	
	LoadIdentifier = AchievementLoadIdentifier;

	//UE_LOG(LogTemp, Warning, TEXT("LevelInformation Num: %d"), LevelInformation.Num());
	//UE_LOG(LogTemp, Warning, TEXT("Level: %d"), Level);
	//UE_LOG(LogTemp, Warning, TEXT("Dungeon: %d"), Dungeon);
	//UE_LOG(LogTemp, Warning, TEXT("Part: %d"), Part);
	//UE_LOG(LogTemp, Warning, TEXT("Difficulty: %d"), Difficulty);
	//UE_LOG(LogTemp, Warning, TEXT("MapName: %s"),*MapName.ToString());

	return AchievementLoadIdentifier;
}

TArray<FString> UTheCaretakerSaveGame::GetKnowSecretCredentials() const
{
	return KnowSecretCredentials;
}

void UTheCaretakerSaveGame::ClearAchievedLevels()
{
	for (int32 i = 0; i < AchievedRewards.Num(); i++)
	{
		AchievedRewards[i].bAchieved = false;
	}
}

void UTheCaretakerSaveGame::ClearKnownSecretSlogans()
{
	SolvedSecretSloganIndices.Empty();
}

void UTheCaretakerSaveGame::SetSecretSloganIndex(int32 Index)
{
	SolvedSecretSloganIndices.Add(Index);
}

UDataTable* UTheCaretakerSaveGame::GetAchievementDefinitions()
{
	return AchievementDefinition;
}

TArray<FAchievement>& UTheCaretakerSaveGame::GetAchievements()
{
	return Achievements;
}

bool UTheCaretakerSaveGame::GetPlayYvesOnce() const
{
	return bYvesPlayedOnce;
}

void UTheCaretakerSaveGame::SetPlayYvesOnce(bool PlayedOnce = true)
{
	bYvesPlayedOnce = PlayedOnce;
}

TArray<FAchieved>& UTheCaretakerSaveGame::GetAchievedRewards()
{
	return AchievedRewards;
}

#pragma endregion

#pragma region Check Definition Setup
void UTheCaretakerSaveGame::CheckDefinitionSetup()
{
	TArray<FName> RowNames = AchievementDefinition->GetRowNames();

	if (AchievedRewards.Num() != RowNames.Num())
	{
		AchievedRewards.Empty();
		for (int i = 0; i < RowNames.Num(); i++)
		{
			AchievedRewards.Add(FAchieved());
		}
	}
}
#pragma endregion

#pragma region Setup PlayModeInformationForLevels
void UTheCaretakerSaveGame::SetupPlayModeInformationForLevels(TArray<FPlayModeInformation>& Information)
{
	if (SolveInformationByPlayModes.Num() > 0)
	{
		LOG_DISPLAY(InitializationLog, "SolveInformation already exist")
		return;
	}

	int32 count = 0;

	for (auto PlayModeInformation : Information)
	{		
		FPlayModeSolveInformation Current = FPlayModeSolveInformation();
		Current.PlayMode = PlayModeInformation.PlayMode;
		for (auto Level : PlayModeInformation.Levels)
		{
			FLevelSolveInformation LevelSolve = FLevelSolveInformation();
			for (auto Dungeon : Level.DungeonsInLevel)
			{
				FDungeonSolveInformation DungeonSolve = FDungeonSolveInformation();
				
				for (auto Difficulty : Dungeon.Difficulties)
				{
					FDungeonDifficultySolveInformation DifficultySolve = FDungeonDifficultySolveInformation();
					DungeonSolve.Difficulties.Add(DifficultySolve);
					count++;
				}

				LevelSolve.Dungeons.Add(DungeonSolve);
			}

			Current.LevelInformation.Add(LevelSolve);
		}

		SolveInformationByPlayModes.Add(Current);
		LOG_DISPLAY(InitializationLog, "SolveInformation added")
	}
}
#pragma endregion

void UTheCaretakerSaveGame::UpdatePlayModeInformationForLevels(TArray<FPlayModeInformation> Information)
{
	if (bExtraLevelsAchievementInformationAdded == true)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Achievement Info already added. Not adding more.")
		return;
	}

	for (int32 j = 0; j < Information.Num(); j++)
	{
		for (int32 i = 0; i < SolveInformationByPlayModes.Num(); i++)
		{
			if (Information[j].PlayMode == SolveInformationByPlayModes[i].PlayMode)
			{
				for (int32 k = 1; k < Information[j].Levels.Num(); k++)
				{
					FLevelSolveInformation LevelSolve = FLevelSolveInformation();
					for (auto Dungeon : Information[j].Levels[k].DungeonsInLevel)
					{
						FDungeonSolveInformation DungeonSolve = FDungeonSolveInformation();

						for (auto Difficulty : Dungeon.Difficulties)
						{
							FDungeonDifficultySolveInformation DifficultySolve = FDungeonDifficultySolveInformation();
							DungeonSolve.Difficulties.Add(DifficultySolve);
						}

						LevelSolve.Dungeons.Add(DungeonSolve);
					}

					SolveInformationByPlayModes[i].LevelInformation.Add(LevelSolve);
				}

				//UE_LOG(LogTemp, Warning, TEXT("%d levels added"), Information[j].Levels.Num()-1);
				//UE_LOG(LogTemp, Warning, TEXT("Solve Information now counts %d elements"), SolveInformationByPlayModes[i].LevelInformation.Num());
			}
		}
	}

	bExtraLevelsAchievementInformationAdded = true;

	LOG_DISPLAY(InitializationLog, "Extra Levels SolveInformation added")
}

#pragma region Completed Current Level
bool UTheCaretakerSaveGame::CompletedCurrentLevel(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32  Part, int32 Difficulty)
{
	UE_LOG(LogTemp, Warning, TEXT("Input: PlayMode: %d, Level: %d, Dungeon: %d, Difficulty: %d, Part: %d"), PlayMode, Level, Dungeon, Difficulty, Part);
	bool AlreadyAchieved = false;
	bool Ok = false;
	LOG_WARNING(RuntimeExecutionLog, "OK Here")
	int32 index = -1;
	for (int32 i = 0; i < SolveInformationByPlayModes.Num(); i++)		
	{
		auto SolveInformation = SolveInformationByPlayModes[i];
		
		if (SolveInformation.PlayMode == PlayMode)
		{
			if (Level >= SolveInformation.LevelInformation.Num())
			{
				LOG_WARNING(RuntimeExecutionLog, "Level index exceeds size of array")
			}
			else
			{
				if (Dungeon >= SolveInformation.LevelInformation[Level].Dungeons.Num())
				{
					LOG_WARNING(RuntimeExecutionLog, "Dungeon index exceeds size of array")
				}
				else
				{
					if (Difficulty >= SolveInformation.LevelInformation[Level].Dungeons[Dungeon].Difficulties.Num())
					{
						LOG_WARNING(RuntimeExecutionLog, "Difficulty index exceeds size of array")
					}
					else
					{
						if (SolveInformationByPlayModes[i].LevelInformation[Level].Dungeons[Dungeon].Difficulties[Difficulty].DungeonParts[Part].bFinished == false)
						{
							SolveInformationByPlayModes[i].LevelInformation[Level].Dungeons[Dungeon].Difficulties[Difficulty].DungeonParts[Part].bFinished = true;
						}
						else
						{
							AlreadyAchieved = true;
						}
						Ok = true;
					}
				}
			}
		}
	}

	if (Ok == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Value Set on Index"), SolveInformation.LevelInformation[Level].Dungeons[Dungeon].Difficulties[Difficulty].DungeonParts[Part].bFinished ? "True" : "False");
		LOG_DISPLAY(RuntimeExecutionLog, "SolveInformation updated with level success")
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Part in SolveInformation")
	}

	return AlreadyAchieved;
}
#pragma endregion

#pragma region Calculate Level Points
int32 UTheCaretakerSaveGame::CalculateLevelPoints()
{
	int32 result = 0;

	if (SolveInformationByPlayModes.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No PlayModeInformation found")
	}
	else
	{
		for (auto SolveInformation : SolveInformationByPlayModes)
		{
			if (SolveInformation.LevelInformation.Num() == 0)
			{
				LOG_WARNING(RuntimeExecutionLog, "No Levels found")
				continue;
			}

			for (auto Level : SolveInformation.LevelInformation)
			{
				if (Level.Dungeons.Num() == 0)
				{
					LOG_WARNING(RuntimeExecutionLog, "No Dungeons found")
					continue;
				}

				for (auto Dungeon : Level.Dungeons)
				{
					if (Dungeon.Difficulties.Num() == 0)
					{
						LOG_WARNING(RuntimeExecutionLog, "No Difficulties found")
						continue;
					}

					for (int i = 0; i < Dungeon.Difficulties.Num(); i++)
					{
						auto Difficulty = Dungeon.Difficulties[i];
						for (auto Part : Difficulty.DungeonParts)
						{
							if (Part.bFinished == true)
							{
								//LOG_DISPLAY(RuntimeExecutionLog, "Adding Difficulty Value")
								result += (i + 1);
							}
						}
					}
				}
			}
		}
	}
								
	return result;
}
#pragma endregion

#pragma region Get Credential Solved Count
int32 UTheCaretakerSaveGame::GetCredentialSolveCount(EPlayMode PlayMode, int32 LevelIndex, int32 DungeonIndex, int32 PartIndex, int32 DifficultyIndex) const
{
	if (PlayMode == EPlayMode::PM_HOPHOP)
	{
		LOG_WARNING(RuntimeExecutionLog, "Shouldn't be called")
	}

	if (DifficultyIndex <= -1)
	{
		DifficultyIndex = 0;
		PartIndex = 0;
	}

	int32 result = 0;

	if (SolveInformationByPlayModes.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No PlayModeInformation found")
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("SolveInformation Count: %d"), SolveInformationByPlayModes.Num());
		for (auto SolveInformation : SolveInformationByPlayModes)
		{
			if (SolveInformation.PlayMode != PlayMode)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Not this PlayMode: %d, SolveInformation: %d"), PlayMode, SolveInformation.PlayMode);
				continue;
			}					
			
			if (SolveInformation.LevelInformation.Num() <= LevelIndex)
			{
				LOG_WARNING(RuntimeExecutionLog, "LevelIndex to high")
				continue;
			}

			auto Level = SolveInformation.LevelInformation[LevelIndex];
			
			if (Level.Dungeons.Num() <= DungeonIndex)
			{
				LOG_WARNING(RuntimeExecutionLog, "DungeonIndex too hight")
				continue;
			}

			auto Dungeon = Level.Dungeons[DungeonIndex];
				
			if (Dungeon.Difficulties.Num() <= DifficultyIndex)
			{
				LOG_WARNING(RuntimeExecutionLog, "DifficultyIndex too high")
				continue;
			}

			for (int32 i = 0; i < DifficultyIndex + 1; i++)
			{
				//UE_LOG(LogTemp, Warning, TEXT("%d"),i);
				auto Difficulty = Dungeon.Difficulties[i];
				auto Part = Difficulty.DungeonParts[PartIndex];
						
				if (Part.bFinished == true)
				{
					LOG_DISPLAY(RuntimeExecutionLog, "Level already solved")
					result ++;
				}
				else
				{
					//UE_LOG(LogTemp, Warning, TEXT("False on: %d"), i);
				}
			}
		}
	}

	UE_LOG(LogTemp, Display, TEXT("CurrentResult: %d, Difficulty: %d"), result, DifficultyIndex);

	return result;
}
#pragma endregion
void UTheCaretakerSaveGame::AddSolvedSecretSloganIndex(int32 index)
{
	if (SolvedSecretSloganIndices.Num() == 0)
	{
		SolvedSecretSloganIndices.Add(index);
	}
	else
	{
		for (auto KnownIndex : SolvedSecretSloganIndices)
		{
			if (KnownIndex == index)
			{
				return;
			}
		}

		SolvedSecretSloganIndices.Add(index);
	}
}

TArray<int32> UTheCaretakerSaveGame::GetSolvedSecretSloganIndices() const
{
	return SolvedSecretSloganIndices;
}


void UTheCaretakerSaveGame::SetGamePlayMode(EPlayMode PlayMode)
{
	GamePlayMode = PlayMode;
}

EPlayMode UTheCaretakerSaveGame::GetGamePlayMode() const
{
	return GamePlayMode;
}

void UTheCaretakerSaveGame::SetCurrentProgress(FCurrentProgress Progress)
{
	CurrentProgress = Progress;
}

FCurrentProgress UTheCaretakerSaveGame::GetCurrentProgress() const
{
	return CurrentProgress;
}

void UTheCaretakerSaveGame::SetTutorialFinished(EPlayMode PlayMode, bool Finished)
{
	if (PlayMode == EPlayMode::PM_CLASSIC)
	{
		bTutorialFinished[0] = Finished;
	}
	else if(PlayMode == EPlayMode::PM_DEFAULT)
	{
		bTutorialFinished[1] = Finished;
	}
}

bool UTheCaretakerSaveGame::GetTutorialFinished(EPlayMode PlayMode) const
{
	if (PlayMode == EPlayMode::PM_DEFAULT)
	{
		return bTutorialFinished[1];
	}
	return bTutorialFinished[0];
}

void UTheCaretakerSaveGame::ShiftToPartTwo()
{
	if (SolveInformationByPlayModes.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No PlayModeInformation found")
	}
	else
	{
		for (int32 l = 0; l < SolveInformationByPlayModes.Num(); l++)
		{
			auto SolveInformation = SolveInformationByPlayModes[l];
			if (SolveInformation.PlayMode != EPlayMode::PM_CLASSIC)
			{
				continue;
			}

			if (SolveInformation.LevelInformation.Num() <= 0)
			{
				LOG_WARNING(RuntimeExecutionLog, "Level not found")
				continue;
			}

			for (int32 i = 0; i < SolveInformation.LevelInformation.Num(); i++)
			{
				auto Level = SolveInformation.LevelInformation[i];

				if (Level.Dungeons.Num() <= 0)
				{
					LOG_WARNING(RuntimeExecutionLog, "Dungeons not found")
					continue;
				}

				for (int32 j = 0; j < Level.Dungeons.Num(); j++)
				{
					auto Difficulty0 = Level.Dungeons[j].Difficulties[0];
					for (int32 k = 0; k < Difficulty0.DungeonParts.Num(); k++)
					{
						SolveInformationByPlayModes[l].LevelInformation[i].Dungeons[j].Difficulties[0].DungeonParts[k].bFinished = true;
					}
				}
			}
		}
	}
	
	bTutorialFinished[0] = true;
}

bool UTheCaretakerSaveGame::HasPartAchieved(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) const
{
	if (Difficulty == -1)
	{
		return false;
	}

	for (int32 i = 0; i < SolveInformationByPlayModes.Num(); i++)
	{
		auto SolveInformation = SolveInformationByPlayModes[i];

		if (SolveInformation.PlayMode != PlayMode)
		{
			continue;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%d levels in Solve Information"), SolveInformation.LevelInformation.Num());
		if (Difficulty == -1)
		{
			Difficulty = 0;
		}
		if (Level == -1)
		{
			Level = 0;
		}
		//return true;
		return SolveInformation.LevelInformation[Level].Dungeons[Dungeon].Difficulties[Difficulty].DungeonParts[Part].bFinished;
	}
	return false;
}

int32 UTheCaretakerSaveGame::CalculateCurrentDifficultyForPart(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Part)
{
	int CurrentDiff = 0;
	for (int32 i = 0; i < SolveInformationByPlayModes.Num(); i++)
	{
		auto SolveInformation = SolveInformationByPlayModes[i];

		if (SolveInformation.PlayMode != PlayMode)
		{
			continue;
		}

		if (Level >= SolveInformation.LevelInformation.Num())
		{
			LOG_WARNING(RuntimeExecutionLog, "LevelIndex too high in Calculate Current Difficulty")
			continue;
		}

		for (int32 j = 0; j < SolveInformation.LevelInformation[Level].Dungeons[Dungeon].Difficulties.Num(); j++)
		{
			auto Difficulty = SolveInformation.LevelInformation[Level].Dungeons[Dungeon].Difficulties[j];

			if (Difficulty.DungeonParts[Part].bFinished == true)
			{
				CurrentDiff++;
			}
			else
			{
				break;
			}
		}

		/// Next 3 lines under inspection. Should be fine, but feels untested ...
		/// If issues with difficulty index, maybe look here
		//if (CurrentDiff == 0)
		//{
		//	if (SolveInformation.LevelInformation[Level].Dungeons[SolveInformation.LevelInformation[Level].Dungeons.Num() - 1].Difficulties[CurrentDiff].DungeonParts[2].bFinished == true)
		//	{
		//		CurrentDiff++;
		//	}
		//}
		//else
		//{
		//	if (SolveInformation.LevelInformation[Level].Dungeons[SolveInformation.LevelInformation[Level].Dungeons.Num() - 1].Difficulties[CurrentDiff - 1].DungeonParts[2].bFinished == true)
		//	{
		//		CurrentDiff++;
		//	}
		//}
	}

	return CurrentDiff;	
}

void UTheCaretakerSaveGame::FullProgress()
{
	if (bIsPart2)
	{
		SetAllProgressValues(true);
	}
	else
	{
		ShiftToPartTwo();
	}
}

void UTheCaretakerSaveGame::ResetProgressData()
{
	SetAllProgressValues(false);
}

void UTheCaretakerSaveGame::UpdateProgressToValues(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part)
{
	LOG_WARNING(RuntimeExecutionLog, "Not written yet")
}

void UTheCaretakerSaveGame::UpdateAchievementLoadIdentifier()
{

}

int32 UTheCaretakerSaveGame::GetCurrentHeatPoints() const
{
	if (&HeatHistory == nullptr)
	{
		return -400;
	}

	

	return HeatHistory.GetHeatPoints();
}

EPlayMode UTheCaretakerSaveGame::HasMostPlayedThisPlayMode() const
{
	if (&HeatHistory == nullptr)
	{
		return EPlayMode::PM_NONE;
	}

	return HeatHistory.HasMostPlayedThisPlayMode();
}

void UTheCaretakerSaveGame::AddHeatPoints(EPlayMode PlayMode, int32 HeatPoints)
{
	//UE_LOG(LogTemp, Warning, TEXT("Adding %d heat points"), HeatPoints);
	HeatHistory.AddHeatPoints(PlayMode, HeatPoints);

	//UE_LOG(LogTemp, Warning, TEXT("Now has %d heat points"), HeatHistory.GetHeatPoints());
}

bool UTheCaretakerSaveGame::HighScoreContainsElements() const
{
	return CompleteHighScore.Num() > 0;
}

void UTheCaretakerSaveGame::AddDefaultHighScore(TArray<FHighScoreComplete> &DefaultHighScore)
{
	CompleteHighScore = DefaultHighScore;
	UE_LOG(LogTemp, Display, TEXT("HighScores added. Now count %d entries"), CompleteHighScore.Num());
}

TArray<FHighScoreEntry> UTheCaretakerSaveGame::GetHighScoresForSettings(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part)
{
	TArray<FHighScoreEntry> ReturnValue = TArray<FHighScoreEntry>();

	if (CompleteHighScore.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "Highscore was null ! This shouldn't happen !")
		return ReturnValue;
	}

	for (auto Entry : CompleteHighScore)
	{
		if (Entry.PlayMode == PlayMode)
		{
			if (Entry.Level == Level || Level == -1 || Entry.Level == -1
				&& Entry.Dungeon == Dungeon || Dungeon == -1 || Entry.Dungeon == -1
				&& Entry.Difficulty == Difficulty || Difficulty == -1 || Entry.Difficulty == -1
				&& Entry.Part == Part || Part == -1 || Entry.Part == -1)
			{
				FHighScoreEntry NewEntry;

				NewEntry.Name = Entry.Name;
				NewEntry.Score = Entry.Score;
				NewEntry.TimeSucceeded = Entry.TimeSucceeded;

				ReturnValue.Add(NewEntry);
			}
		}
	}

	QuickSortHighScore(ReturnValue, 0, ReturnValue.Num() - 1);

	return ReturnValue;
}

void UTheCaretakerSaveGame::QuickSortHighScore(TArray<FHighScoreEntry>& HighScore, int32 Start, int32 End)
{
	if (Start < End)
	{
		int32 Part_Index = PartitionHighScore(HighScore, Start, End);
		QuickSortHighScore(HighScore, Start, Part_Index - 1);
		QuickSortHighScore(HighScore, Part_Index + 1, End);
	}
}

int32 UTheCaretakerSaveGame::PartitionHighScore(TArray<FHighScoreEntry>& HighScore, int32 Start, int32 End)
{
	int32 Pivot = HighScore[End].Score;

	int32 P_Index = Start;

	FHighScoreEntry temp;

	for (int32 i = Start; i < End; i++)
	{
		if (HighScore[i].Score > Pivot)
		{
			temp = HighScore[i];
			HighScore[i] = HighScore[P_Index];
			HighScore[P_Index] = temp;
			P_Index++;
		}
	}

	temp = HighScore[End];
	HighScore[End] = HighScore[P_Index];
	HighScore[P_Index] = temp;

	return P_Index;
}

void UTheCaretakerSaveGame::AddHighScore(FHighScoreComplete HighScoreEntry)
{
	CompleteHighScore.Add(HighScoreEntry);
	UE_LOG(LogTemp, Warning, TEXT("Added entry. Highscore now has %d entries"), CompleteHighScore.Num());
}

const bool UTheCaretakerSaveGame::IsSecretSolved(int32 Index) const
{
	if (SolvedSecretSloganIndices.Num() == 0)
	{
		return false;
	}

	for (auto SolvedIndex : SolvedSecretSloganIndices)
	{
		if (SolvedIndex == Index)
		{
			return true;
		}
	}

	return false;
}

void UTheCaretakerSaveGame::SetAllProgressValues(bool Value)
{
	if (SolveInformationByPlayModes.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No PlayModeInformation found")
	}
	else
	{
		for (int32 i = 0; i < SolveInformationByPlayModes.Num(); i++)
		{
			for (int32 j = 0; j < SolveInformationByPlayModes[i].LevelInformation.Num(); j++)
			{
				for (int32 k = 0; k < SolveInformationByPlayModes[i].LevelInformation[j].Dungeons.Num(); k++)
				{
					for (int32 l = 0; l < SolveInformationByPlayModes[i].LevelInformation[j].Dungeons[k].Difficulties.Num(); l++)
					{
						for (int32 m = 0; m < SolveInformationByPlayModes[i].LevelInformation[j].Dungeons[k].Difficulties[l].DungeonParts.Num(); m++)
						{
							SolveInformationByPlayModes[i].LevelInformation[j].Dungeons[k].Difficulties[l].DungeonParts[m].bFinished = Value;
						}
					}
				}
			}
		}
	}
}

