/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "CurrentProgress.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct THECARETAKER_API FCurrentProgress
{
	GENERATED_BODY()

public:
	FCurrentProgress();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentDungeon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevelPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPartInformation> CurrentPart;

public:
	void SetCurrentLevelName(FName Name);
	void SetCurrentLevel(int32 Level);
	void SetCurrentDungeon(int32 Dungeon);
	void SetCurrentPart(EPartInformation Part);
	void SetCurrentDifficulty(int32 Difficulty);
};