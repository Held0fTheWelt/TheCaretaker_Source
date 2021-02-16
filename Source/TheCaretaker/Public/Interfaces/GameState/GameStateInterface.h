/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/Achievement/AchievementType.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Enums/Score/ScoreType.h"
#include "Interfaces/DungeonMaster/DungeonMasterInterface.h"
#include "GameInstance/GameInstanceManager.h"
#include "GameStateInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IGameStateInterface
{
	GENERATED_BODY()

public:
	virtual bool SetupGameState(class UMainUI* UI) = 0;
	virtual void SetGarbageToCollect(int8 NewGarbageCount) = 0;
	virtual void IncrementGarbageToCollect() = 0;
	virtual void IncrementTrapsToSolve() = 0;
	virtual void SetTrapsToSolve(int8 NewTrapCount) = 0;
	virtual void SetChestsToSolve(int8 NewChestCount) = 0;
	virtual void IncrementChestsToSolve() = 0;
	virtual int8 GetCurrentChestCount() const = 0;
	virtual void CountDownChests(TEnumAsByte<EPartInformation> Part) = 0;
	virtual void CountDownTraps() = 0;
	virtual void CountDownGarbage(class AFireplaceActor* Fireplace) = 0;
	virtual void MonsterIsAngry() = 0;
	virtual void MonsterNotAngryAnymore() = 0;
	virtual EPartInformation GetCurrentPart() const = 0;
	virtual void SetCurrentPart(EPartInformation CurrentPart) = 0;
	virtual void SetCurrentDungeon(int32 CurrentDungeon) = 0;
	virtual void SetCurrentLevel(int32 CurrentLevel) = 0;
	virtual int32 GetCurrentLevel() const = 0;
	virtual int32 GetCurrentDungeon() const = 0;
	virtual int32 GetCurrentDifficulty() const = 0;
	virtual void UpdateCurrentInfos(FCurrentProgress CurrentProgress) = 0;
	virtual void RegisterDungeonMaster(IDungeonMasterInterface* Interface) = 0;
	virtual void SetShouldWaitForEndOfTime(bool ShouldWaitForEndOfTime) = 0;
	virtual void StopCredentialTimer() = 0;
	virtual void CalculateScoreAddition(EScoreType ScoreToAdd) = 0;
	virtual void AddTrapObjective(EPartInformation Part) = 0;
	virtual void AchievementSolved(EAchievementType AchievementType) = 0;
	virtual void AddGoldObjective() = 0;
	virtual void RemoveGoldObjective() = 0;
	virtual FHighScoreEntry GetHighScoreEntry() const = 0;
	virtual void ContinueGamePlay() = 0;
};
