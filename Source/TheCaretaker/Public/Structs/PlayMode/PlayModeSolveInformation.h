/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Structs/Level/LevelSolveInformation.h"
#include "PlayModeSolveInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPlayModeSolveInformation
{
	GENERATED_BODY()

public:
	FPlayModeSolveInformation();


public:
	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	TArray<FLevelSolveInformation> LevelInformation;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	EPlayMode PlayMode;
};

