/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Structs/Part/PartInformation.h"
#include "Interfaces/SpawnPoints/ObjectiveSpawnPointInterface.h"
#include "Interfaces/SpawnPoints/SpawnOnFloorInterface.h"
#include "Structs/Spawning/LocalSpawnInformation.h"
#include "Structs/Spawning/SpawnInformationTable.h"
#include "Structs/Level/LevelInformation.h"

#include "GameMode_Game.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AGameMode_Game : public AGameModeBase, public IGameModeInterface, public IPauseGameInterface
{

	GENERATED_BODY()
	
public:
	AGameMode_Game();

	virtual void BeginPlay() override;

	void SetTitle(TAssetPtr<class UFMODEvent> Title);

protected:
	//virtual void SetupMonstersToFeed(UWorld* World) override;

	virtual void Tick(float DeltaTime) override;
	virtual void RegisterMonstersToFeed(UWorld* World);

protected:
	void InitGameSettings();
	bool SetupUI();
	virtual void SpawnMusic();
	void RegisterAllActors();
	virtual void ShowMessagesOnScreen();
	bool PrepareGameSpawningInformation();

private:
	void BroadcastNewGameStart(UWorld* World);
	bool GetInstanceInterfaces();
	bool GetFMODParameters();
	bool GetGameStateInterface();
	bool LoadLevel();
	void SetupUIInformation();
	void UpdateClock();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UClockComponent* ClockComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UFMODAudioComponent* MusicComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Information")
	class UDataTable* SpawnInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn Information")
	FLocalSpawnInformation SpawnSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock Settings | Calculation")
	float ClockMaxTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Setup | FMOD")
	EFMODParameterType FMODParameterType;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Analysis | FMOD")
	FName FMODParameterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Analysis | FMOD")	
	float FMODSoundChangeValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAudioComponent* ScoreAdditionAudioComponent;

	bool bGameModeTutorial;
private:	
	class IGameStateInterface* GameStateInterface;

	class IGameInstanceInterface* GameInstance;
	class IGameInstanceAccessoryInterface* GameInstanceAccessory;
	class IGameInstanceUIInterface* GameInstanceUI;

	UPROPERTY(VisibleAnywhere, Category = "Analysis | Pause")	
	bool bPaused;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Spawning")	
	TArray<FGarbageSpawnInformation> GarbageSpawnInformation;
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Spawning")	
	TArray<FChestSpawnInformation> ChestSpawnInformation;
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Spawning")	
	TArray<FTrapSpawnInformation> TrapSpawnInformation;
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Spawning")	
	TArray<FSpiderSpawnInformation> SpiderSpawnInformation;
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Current Progress")	
	TArray<FLevelInformation> LevelInformation;
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Current Progress")	
	FPartInformation CurrentDungeonPartInformation;

protected:
	// Inherited via IPauseGameInterface
	virtual void SetGamePaused(bool SetGamePaused) override;

	virtual bool IsPaused() const;

private:
	void SetupLevelDoors();
	void LoadSublevels();
	void Spawn();
	bool TestGameStateSetup();
	void CheckScoreSetup();

protected:
	bool PrepareSpawnInformation();
	TArray<IObjectiveSpawnPointInterface*> GetSpawnPoints(TArray<IObjectiveSpawnPointInterface*> InputPoints, TEnumAsByte<ESpawnPointType> SpawnPointType, EPartInformation Part) const;
	TArray<ISpawnOnFloorInterface*> GetSpawnPoints(TArray<ISpawnOnFloorInterface*> InputPoints, TEnumAsByte<ESpawnPointType> SpawnPointType, EPartInformation Part) const;
	void ShuffleArray(TArray<IObjectiveSpawnPointInterface*>& SpawnPointArray);
	void ShuffleArray(TArray<ISpawnOnFloorInterface*>& SpawnPointArray);
	virtual void SpawnGarbage(TArray<ISpawnOnFloorInterface*> SpawnPointArray, EPartInformation Part);
	virtual void SpawnChests(TArray<IObjectiveSpawnPointInterface*> ChestPoints, EPartInformation Part);
	virtual void SpawnTraps(TArray<IObjectiveSpawnPointInterface*> TrapPoints, EPartInformation Part);
	virtual void SpawnSpiders(TArray<IObjectiveSpawnPointInterface*> SpiderPoints, EPartInformation Part);
	
public:
	UFUNCTION()
	void CallbackOnLevelLoaded();

	class IClockInterface* GetClock();
	virtual UFMODAudioComponent* GetFMODComponent();
	virtual void SetClockActive(bool SetActive) override;
	virtual void ClockRunningBackwards(bool SetActive) override;

	virtual void AddScoreSound(class USoundBase* SoundForAddingScore) override;
	virtual void PlayScoreSound(bool Play) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup | Drop")
	float ChanceToOpenClosedChest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup | Drop")
	float ChanceToReleaseTrap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup | FMOD")
	class UCurveFloat* MusicDynamics;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock Settings | Initialization")
	float DelayClockStart;

	FTimerHandle TimerHandle_ClockDelay;
private:
	virtual void DropGarbage() override;
	virtual void DropGold() override;
	virtual void DropTrap() override;

	UFUNCTION()
	void StartClock();

	// Inherited via IGameModeInterface
	virtual FTimeSet GetCurrentTime() override;

	// Inherited via IGameModeInterface
	virtual TArray<FGarbageSpawnInformation> GetGarbageSpawnInformation() const override;
};
