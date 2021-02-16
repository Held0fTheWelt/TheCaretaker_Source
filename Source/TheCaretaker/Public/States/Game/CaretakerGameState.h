/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Structs/Anger/MonsterAnger.h"
#include "Interfaces/Clock/ClockInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Structs/Part/PartInformation.h"
#include "Structs/Score/ScoreCalculator.h"
#include "Structs/Score/HighScoreEntry.h"
#include "CaretakerGameState.generated.h"



/**
 * 
 */
UCLASS()
class THECARETAKER_API ACaretakerGameState : public AGameStateBase, public IGameStateInterface
{
	GENERATED_BODY()
	
public:
	ACaretakerGameState();

	virtual void BeginPlay() override;
#pragma region Widgets & Pointer
public:
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UMainUI* MainUI;

	// Widget to handle Screen Notifications
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UScreenNotification* ScreenNotifications;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UMiniMapWidget* MiniMap;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UMonsterHungerViewWidget* Monsters;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UInventoryWidget* DebugInventory;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UInformationWidget* Information;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UTimeInformationWidget* Clock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float TimeToShowScore;
#pragma endregion

	virtual void HandleBeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	
	virtual bool SetupGameState(class UMainUI* UI) override;

	
public:

#pragma region Ingame Management
	virtual void SetGarbageToCollect(int8 NewGarbageCount) override;
	virtual void SetTrapsToSolve(int8 NewTrapCount) override;
	virtual void SetChestsToSolve(int8 NewChestCount) override;

	void SetupScore();
	void NotCompeting();

public:

	UPROPERTY(VisibleAnywhere, Category = "Secret")
	float TimeToShowCredentials;

	UPROPERTY(VisibleAnywhere, Category = "Game Count")
	int8 GarbageCount;
	int8 GarbageMax;
	UPROPERTY(VisibleAnywhere, Category = "Game Count")
	int8 TrapCount;
	int8 TrapMax;
	UPROPERTY(VisibleAnywhere, Category = "Game Count")
	int8 ChestCount;
	int8 ChestMax;

	UPROPERTY(VisibleAnywhere, Category = "Game Count")
	FMonsterAnger  MostAngryMonster;
	UPROPERTY(VisibleAnywhere, Category = "Game Count")
	float Angryness;

	UPROPERTY(VisibleAnywhere, Category = "Game Count")
	bool bShouldWaitForEndOfTime;
#pragma endregion

#pragma region GameSettings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Information")
	int32 CurrentLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Information")
	int32 CurrentDungeon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Information")
	TEnumAsByte<EPartInformation> CurrentPart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Information")
	int32 CurrentDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Information")
	int32 CurrentScore;
#pragma endregion

#pragma region Score
	UPROPERTY(EditDefaultsOnly, Category = "Score")
	class UDataTable* ScoreDefinition;
		
	UPROPERTY(EditDefaultsOnly, Category = "Score")
	class UDataTable* ScoreMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = "Score")
	class UDataTable* TimeToScore;

	UPROPERTY(VisibleAnywhere, Category = "Score")
	FScoreCalculator ScoreCalculator;
#pragma endregion
public:
	UFUNCTION()
	void GoldCollected();
	UFUNCTION()
	void GarbageCollected(TEnumAsByte<EPartInformation> Part);
	UFUNCTION()
	virtual void CountDownTraps() override;
	UFUNCTION()
	virtual void CountDownGarbage(class AFireplaceActor* Fireplace) override;
	UFUNCTION()
	virtual void MonsterIsAngry() override;
	UFUNCTION()
	virtual void MonsterNotAngryAnymore() override;
	UFUNCTION()
	virtual void CountDownChests(TEnumAsByte<EPartInformation> Part) override;
	
	UFUNCTION()
	virtual void WinConditionEntered();

	UFUNCTION()
	void FinishLevel();
	UFUNCTION()
	void ShowHighScore();
	UFUNCTION()
	void HideHighScore();

	virtual void StopCredentialTimer() override;

	UFUNCTION()
	void MonsterReport(FMonsterAnger MonsterAnger);

	UPROPERTY()
	TArray<FMonsterAnger> MonstersAnger;

private:
	UFUNCTION()
	void CountVictory();

	UFUNCTION()
	void UpdateCurrentHighScore();

	FTimerHandle TimerHandle_FinishDelay;
	FTimerHandle TimerHandle_ScoreDelay;
	bool WinConditionMet() const;

	UFUNCTION()
	void ShowNewCredentials();
	UFUNCTION()
	void SmallCredentialsDelay();

	UFUNCTION()
	void HideFinalScore();

	virtual EPartInformation GetCurrentPart() const override;
	virtual int32 GetCurrentDungeon() const override;
	virtual int32 GetCurrentLevel() const override;
	virtual void UpdateCurrentInfos(FCurrentProgress CurrentProgress) override;
	virtual int8 GetCurrentChestCount() const override;
	virtual void RegisterDungeonMaster(IDungeonMasterInterface * Interface) override;
	virtual void SetShouldWaitForEndOfTime(bool ShouldWaitForEndOfTime) override;
	virtual void SetCurrentPart(EPartInformation CurrentPart) override;
	virtual void SetCurrentDungeon(int32 CurrentDungeon) override;
	virtual void SetCurrentLevel(int32 CurrentLevel) override;
	virtual int32 GetCurrentDifficulty() const override;
	virtual void CalculateScoreAddition(EScoreType ScoreToAdd) override;

	UFUNCTION()
	void PerformLevelChange();

	UFUNCTION()
	void PlayerKilledByMaster();

	void ReadInScoreSetup();
	void ReadInScoreDefinition();
	void ReadInScoreMultiplier();
	void ReadInTimesToScore();
	void ReadInMaxTime();
	void ReadInDifficulty();
	void ShowScoreCalculatorValues();
	void ResetCalculationScoreValues();

	virtual FHighScoreEntry GetHighScoreEntry() const override;

private:
	IClockInterface* ClockInterface;
	IGameInstanceAccessoryInterface* GameInstanceInterface;

	class UCurrentScoreUserWidget* CurrentScoreWidget;

	class ACaretakerPlayerState* PlayerState;

	FTimerHandle TimerHandle_ShowCredentials;

	bool bScoreSetupOkay;


	// Inherited via IGameStateInterface
	virtual void AddTrapObjective(EPartInformation Part) override;

	virtual void AddGoldObjective() override;
	virtual void RemoveGoldObjective() override;

	// Inherited via IGameStateInterface
	virtual void AchievementSolved(EAchievementType AchievementType) override;

	// Inherited via IGameStateInterface
	virtual void IncrementGarbageToCollect() override;
	virtual void IncrementTrapsToSolve() override;
	virtual void IncrementChestsToSolve() override;

	// Inherited via IGameStateInterface
	virtual void ContinueGamePlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void LevelComplete();
public:
	UFUNCTION(BlueprintImplementableEvent)
	void LevelFailed();
};
