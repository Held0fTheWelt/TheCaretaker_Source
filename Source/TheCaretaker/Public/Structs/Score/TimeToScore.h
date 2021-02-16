/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/Score/ScoreType.h"
#include "TimeToScore.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FTimeToScore : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTimeToScore();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScoreType ScoreType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToScore;
};
