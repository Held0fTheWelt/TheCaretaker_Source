/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "DifficultyMultiplier.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FDifficultyMultiplier
{
	GENERATED_BODY()

public:
	FDifficultyMultiplier();

	UPROPERTY()
	TArray<float> Modifier;
};
