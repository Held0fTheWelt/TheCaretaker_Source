/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "HighScoreEntry.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FHighScoreEntry
{
	GENERATED_BODY()

public:
	FHighScoreEntry();

public:
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	float TimeSucceeded;
	UPROPERTY(EditAnywhere)
	int32 Score;
};
