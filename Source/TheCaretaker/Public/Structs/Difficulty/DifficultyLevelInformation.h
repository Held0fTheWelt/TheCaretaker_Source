/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "DifficultyLevelInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FDifficultyLevelInformation
{
	GENERATED_BODY()

public:
	FDifficultyLevelInformation();

public:
	UPROPERTY()
	int32 NumberOfGarbage;
	UPROPERTY()
	int32 NumberOfChests;
	UPROPERTY()
	int32 NumberOfTraps;
	UPROPERTY()
	TArray<float> TimesToGetHungry;
	UPROPERTY()
	bool bWaitForEndOfTime;
	UPROPERTY()
	float TimeToSolveInSeconds;

};
