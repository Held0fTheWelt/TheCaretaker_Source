/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "Enums/SpawnPointType/SpawnPointType.h"
#include "Enums/PlayPath/PlayPath.h"
#include "Enums/PowerUp/PowerUpSelection.h"
#include "UObject/Interface.h"
#include "Structs/Achievement/Achievement.h"
#include "Structs/Achievement/AchievementDefinition.h"
#include "Structs/FMOD/FMODParameterSetList.h"
#include "Structs/Level/LevelInformation.h"
#include "Structs/Part/PartInformation.h"
#include "Structs/CurrentProgress/CurrentProgress.h"
#include "Structs/PlayMode/PlayModeInformation.h"
#include "Structs/PlayMode/PlayModeModifierInformation.h"
#include "Structs/Score/HighScoreEntry.h"
#include "GameInstanceAccessoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameInstanceAccessoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IGameInstanceAccessoryInterface
{
	GENERATED_BODY()
			
public:
	virtual FName GetMenuLevelName() const = 0;
	virtual FName GetTutorialLevelName() const = 0;
	virtual TArray<int32> GetSlogansIndicesLevelpoints() const = 0;
	virtual TArray<FAchievementDefinition> GetAchievements() = 0;
	virtual TArray<FLevelInformation> GetLevelInformation() const = 0;
	virtual class IGameStateInterface* GetGameState() = 0;
	virtual void SetCurrentDungeonPartInfos(int32 CurrentLevel, int32 CurrentDungeon, TEnumAsByte<EPartInformation> CurrentPart) = 0;
	virtual FName GetCurrentLevelName() const = 0;
	virtual void SetCurrentLevelName(FName NewLevelName) = 0;
	virtual void SetLastLevelName() = 0;
	virtual FAchievementLoadIdentifier GetLoadIdentifier() = 0;
	virtual TArray<FAchieved> GetAchievedRewards() = 0;
	virtual FMODParameterSet GetFMODParameterSet(EFMODParameterType ParameterType) = 0;
	virtual FCurrentProgress GetCurrentProgress() const = 0;
	virtual FName GetLevelName(int32 CurrentLevel, int32 CurrentDungeon) = 0;
	virtual bool IsSecretAccessible(FString SecretCode) = 0;
	virtual FPlayModeInformation GetPlayModeInformation(EPlayMode PlayMode) const = 0;
	virtual FPlayModeModifierInformation GetPlayModeModifierInformation(EPlayMode PlayMode) const = 0;
	virtual EPlayMode GetPlayMode() const = 0;
	virtual int32 GetNumberToSpawn(ESpawnPointType SpawnPointType, EPartInformation CurrentPart) = 0;
	virtual int32 GetSpiderPathNumber(EPartInformation CurrentPart) const = 0;
	virtual TArray<float> GetSpiderPathSpreadValues(EPartInformation CurrentPart) const = 0;
	virtual float GetTimeToGetHungry(EPartInformation CurrentPart) = 0;
	virtual FCharacterSetup GetCharacterSetup() const = 0;
	virtual FSpiderSetup GetSpiderSetup() const = 0;
	virtual FClockSetup GetClockSetup() const = 0;
	virtual bool ShouldWaitForEndOfTime() const = 0;
	virtual bool ConsoleInfoShown() const = 0;
	virtual void SetConsoleInfoShown(bool InfoShown) = 0;
	virtual int32 GetCurrentLevelPoints() const = 0;
	virtual int32 GetCurrentDifficulty() const = 0;
	virtual int32 CalculateCurrentDifficulty() = 0;
	virtual int32 GetMaxDifficulties(int32 Level, int32 Dungeon) const = 0;
	virtual int32 CalculateCurrentDifficultyForPart(int32 Level, int32 Dungeon, int32 Part) = 0;
	virtual void CountBeforeBackToMenu() = 0;
	virtual void ResetTestModes() = 0;
	virtual void SetCurrentDifficulty(int32 Difficulty) = 0;
	virtual bool IsPart2() const = 0;
	virtual bool HasTutorialFinished() const = 0;
	virtual bool HasPartAchieved(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) const = 0;
	virtual TArray<TArray<TArray<FSecretCredential>>> GetKnownSecretCredentialsByArrays(int32 CurrentLevel) const = 0;
	virtual TArray<int32> GetSolvedSloganIndices() const = 0;
	virtual TArray<int32> GetCurrentSolvedSloganIndices() const = 0;
	virtual TArray<FString> GetSecretSlogans() const = 0;
	virtual bool CompetitionAvailable() const = 0;
	virtual int32 GetCurrentHeatPoints() const = 0;
	virtual EPlayMode GetCurrentPreferredPlayMode() const = 0;
	virtual bool IsCompeteAccessible() const = 0;
	virtual class UCurrentScoreUserWidget* AddScoreWidget() = 0;
	virtual EPlayPath GetCurrentPlayPath() const = 0;
	virtual bool IsNewHighScoreAchieved(const int32 Level, const int32 Dungeon, const int32 Difficulty, const int32 Part, const int32 Score, const float Time) = 0;
	virtual TArray<FHighScoreEntry> GetHighScoresForSettings(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) = 0;
	virtual void UpdateHighScoreWidget(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) = 0;
	virtual void PickupCollected(TSubclassOf<class APowerUp>) = 0;
	virtual void PickupDropped(FVector Location) = 0;
	virtual bool HasPickupSpawnLocation(FName PickupName) const = 0;
	virtual FVector GetSpawnLocation(FName PickupName) const = 0;
	virtual void SetSpawnLocation(FName PickupName, FVector SpawnLocation) = 0;
	virtual bool IsPowerUpAvailable(TSubclassOf<class APowerUp> PowerUp) const = 0;
};
