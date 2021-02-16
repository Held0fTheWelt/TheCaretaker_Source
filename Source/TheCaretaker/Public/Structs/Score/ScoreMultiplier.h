/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/Score/ScoreModifier.h"
#include "ScoreMultiplier.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FScoreMultiplier : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScoreMultiplier();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScoreModifierType ScoreModifierType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ModifierValue;
};
