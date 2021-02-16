/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/Score/ScoreType.h"
#include "ScoreDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FScoreDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScoreDefinition();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ScoreName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScoreType ScoreType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScoreValue;
};
