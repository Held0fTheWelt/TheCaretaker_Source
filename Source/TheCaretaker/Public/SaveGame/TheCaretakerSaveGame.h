/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structs/PlayMode/PlayModeSolveInformation.h"
#include "Structs/Achievement/Achievement.h"
#include "Structs/CurrentProgress/CurrentProgress.h"
#include "Structs/GameSecrets/GameSecrets.h"
#include "Structs/Heat/HeatHistory.h"
#include "Structs/Level/LevelInformation.h"
#include "Structs/PlayMode/PlayModeInformation.h"
#include "Structs/Score/HighScoreEntry.h"
#include "Structs/Score/HighScoreComplete.h"
#include "TheCaretakerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UTheCaretakerSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UTheCaretakerSaveGame();

public:
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Achievements")
	class UDataTable* AchievementDefinition;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	TArray<FAchievement> Achievements;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	TArray<FAchieved> AchievedRewards;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	TArray<FPlayModeSolveInformation> SolveInformationByPlayModes;

	TArray<FPlayModeSolveInformation> GetSolveInformationByPlayModes() const;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	TArray<FString> KnowSecretCredentials;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	FAchievementLoadIdentifier LoadIdentifier;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	FHeatHistory HeatHistory;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	TArray<FHighScoreComplete> CompleteHighScore;
public:
	UFUNCTION()
	virtual FAchievementLoadIdentifier GetLoadIdentifier(TArray<FLevelInformation> LevelInformation);

	TArray<FString> GetKnowSecretCredentials() const;

	void ClearAchievedLevels();
	void ClearKnownSecretSlogans();
	void SetSecretSloganIndex(int32 Index);

	UFUNCTION()
	virtual class UDataTable* GetAchievementDefinitions();
	virtual TArray<FAchievement>& GetAchievements();
	virtual TArray<FAchieved>& GetAchievedRewards();
	   
	

	UFUNCTION()
	bool GetPlayYvesOnce() const;

	UFUNCTION()
	void SetPlayYvesOnce(bool PlayedOnce);

	virtual void CheckDefinitionSetup();

	bool CompletedCurrentLevel(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Part, int32 Difficulty);
	
	void SetupPlayModeInformationForLevels(TArray<FPlayModeInformation> &PlayModeInformation);
	
	void UpdatePlayModeInformationForLevels(TArray<FPlayModeInformation> PlayModeInformation);

	int32 CalculateLevelPoints();

	int32 GetCredentialSolveCount(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Part, int32 Difficulty) const;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	bool bIsPart2;


	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	bool bConsoleInfoShown;

	void AddSolvedSecretSloganIndex(int32 index);
	TArray<int32> GetSolvedSecretSloganIndices() const;

	void SetGamePlayMode(EPlayMode PlayMode);
	EPlayMode GetGamePlayMode() const;

	void SetCurrentProgress(FCurrentProgress CurrentProgress);
	FCurrentProgress GetCurrentProgress() const;

	void SetTutorialFinished(EPlayMode PlayMode, bool Finished);

	bool GetTutorialFinished(EPlayMode PlayMode) const;

	void ShiftToPartTwo();

	bool HasPartAchieved(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) const;

	int32 CalculateCurrentDifficultyForPart(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Part);

	void FullProgress();

	void ResetProgressData();

	void SetAllProgressValues(bool Value);

	void UpdateProgressToValues(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part);

	void UpdateAchievementLoadIdentifier();

	int32 GetCurrentHeatPoints() const;

	EPlayMode HasMostPlayedThisPlayMode() const;

	void AddHeatPoints(EPlayMode PlayMode, int32 HeatPoints);

	bool HighScoreContainsElements() const;

	void AddDefaultHighScore(TArray<FHighScoreComplete> &DefaultHighScore);

	TArray<FHighScoreEntry> GetHighScoresForSettings(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part);

	void QuickSortHighScore(TArray<FHighScoreEntry> &HighScore, int32 Start, int32 End);
	int32 PartitionHighScore(TArray<FHighScoreEntry> &HighScore, int32 Start, int32 End);

	void AddHighScore(FHighScoreComplete HighScoreEntry);

	const bool IsSecretSolved(int32 Index) const;
private:
	UPROPERTY(SaveGame)
	TArray<bool> bTutorialFinished;

	UPROPERTY(SaveGame)
	bool bYvesPlayedOnce;

	UPROPERTY(SaveGame)
	FGameSecrets GameSecrets;

	UPROPERTY(SaveGame)
	TArray<int32> SolvedSecretSloganIndices;

	UPROPERTY(SaveGame)
	EPlayMode GamePlayMode;

	UPROPERTY(SaveGame)
	FCurrentProgress CurrentProgress;

	UPROPERTY(SaveGame)
	bool bExtraLevelsAchievementInformationAdded;
};
