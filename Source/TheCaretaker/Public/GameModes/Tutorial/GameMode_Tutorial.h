/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Game/GameMode_Game.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Structs/Tutorial/PlayModeTutorialInformation.h"
#include "GameMode_Tutorial.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AGameMode_Tutorial : public AGameMode_Game, public ITutorialInterface
{
	GENERATED_BODY()
	
public:
	AGameMode_Tutorial();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SpawnMusic() override;

	virtual void ShowMessagesOnScreen() override;
		
	virtual void SpawnChests(TArray<IObjectiveSpawnPointInterface*> ChestPoints, EPartInformation Part) override;
	virtual void SpawnTraps(TArray<IObjectiveSpawnPointInterface*> TrapPoints, EPartInformation Part) override;
	virtual void SpawnSpiders(TArray<IObjectiveSpawnPointInterface*> SpiderPoints, EPartInformation Part) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	TArray<FPlayModeTutorialInformation> TutorialInformation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	FText TitleOnStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial", meta = (MultiLine = true))
	TArray<FText> MessagesOfTutorial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tutorial")
	int32 CurrentProgressIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	float TimeToShowJustText;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tutorial")
	float CurrentTimeTextShown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	float TutorialNoiseMultiplier;

private:
	void WaitForMovement();
	void SpawnAChest();
	void SpawnAGarbage();
	void SpawnASpider();
	void SpawnATrap();
	void ShowClockMessage();
	void SpawnAMonster();
	void WaitForRunning();
	void FinishBasicsMessage();
	void LoadLevel1();

private:

	class APlayerController* PlayerController;
	IGameInstanceUIInterface* GameInstanceUI;
	IGameStateInterface* GameStateInterface;
	bool bStateInitialized;
	EPlayMode CurrentPlayMode;

private:
	virtual void SetNextIndex() override;
	virtual void CommitFalseMessage(FText Message) override;
	virtual int32 GetCurrentTutorialIndex();
	FPlayModeTutorialInformation* CurrentPlayModeInformation;
};
