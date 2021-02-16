/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/PlayMode/PlayMode.h"
#include "HighScoreComplete.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FHighScoreComplete : public FTableRowBase
{
	GENERATED_BODY()

public:
	FHighScoreComplete();

public:
	UPROPERTY(EditAnywhere)
	EPlayMode PlayMode;
	UPROPERTY(EditAnywhere)
	int32 Level;
	UPROPERTY(EditAnywhere)
	int32 Dungeon;
	UPROPERTY(EditAnywhere)
	int32 Part;
	UPROPERTY(EditAnywhere)
	int32 Difficulty;

	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	float TimeSucceeded;
	UPROPERTY(EditAnywhere)
	int32 Score;
	UPROPERTY(EditAnywhere)
	FDateTime DateOfPlayedScore;
	UPROPERTY(EditAnywhere)
	int32 BonusPickups;
};
