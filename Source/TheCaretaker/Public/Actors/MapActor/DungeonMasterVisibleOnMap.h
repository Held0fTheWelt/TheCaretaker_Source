/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/MapActor/ActorVisibleOnMap.h"
#include "Interfaces/DungeonMaster/SpawnDungeonMasterInterface.h"
#include "DungeonMasterVisibleOnMap.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ADungeonMasterVisibleOnMap : public AActorVisibleOnMap, public ISpawnDungeonMasterInterface
{
	GENERATED_BODY()
	
public:
	ADungeonMasterVisibleOnMap();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	class UAudioComponent* AudioComponent;

public:
	UPROPERTY(VisibleAnywhere, Category = Components)
	class USceneComponent* SpawnPointForDungeonMaster;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ADungeonMasterCharacter> DungeonMasterTemplate;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ASimpleChaseAIController> DungeonMasterAITemplate;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Dungeon Master | Sleep")
	class USoundBase* DungeonMasterSleep;
	UPROPERTY(EditAnywhere, Category = "Dungeon Master | Sleep")
	float VolumeForMasterSleep;
	UPROPERTY(EditAnywhere, Category = "Dungeon Master | Sleep")
	bool bMasterSleepIsUISound;
	UPROPERTY(EditAnywhere, Category = "Dungeon Master | WakeUp")
	class USoundBase* DungeonMasterWakeUp;
	UPROPERTY(EditAnywhere, Category = "Dungeon Master | WakeUp")
	bool bMasterAwakeIsUISound;
	UPROPERTY(EditAnywhere, Category = "Dungeon Master | WakeUp")
	float VolumeForMasterWakeUp;
public:
	virtual void SpawnChasingDungeonMaster() override;

};
