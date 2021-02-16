/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Structs/Score/HighScoreEntry.h"
#include "HighScore.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FHighScore : public FTableRowBase
{
	GENERATED_BODY()

public:
	FHighScore();

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
	TArray<FHighScoreEntry> Entries;
};
