/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/TimeSet/TimeSet.h"
#include "Structs/Spawning/SpawnInformationTable.h"
#include "GameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IGameModeInterface
{
	GENERATED_BODY()
			
public:
	virtual class UFMODAudioComponent* GetFMODComponent() = 0;
	virtual void SetClockActive(bool SetActive) = 0;
	virtual void ClockRunningBackwards(bool SetActive) = 0;
	virtual void DropGarbage() = 0;
	virtual void DropGold() = 0;
	virtual void DropTrap() = 0;
	virtual FTimeSet GetCurrentTime() = 0;
	virtual void AddScoreSound(class USoundBase* SoundForAddingScore) = 0;
	virtual void PlayScoreSound(bool Play) = 0;
	virtual TArray<FGarbageSpawnInformation> GetGarbageSpawnInformation() const = 0;
};
