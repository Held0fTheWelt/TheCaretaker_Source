/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameModes/FinishedTimed/FinishedTimedGameMode.h"
#include "FinishedLevelsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AFinishedLevelsGameMode : public AFinishedTimedGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
