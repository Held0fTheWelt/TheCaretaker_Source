/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Misc/DateTime.h"
#include "HeatHistory.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FHeatHistoryPerPlayMode
{
	GENERATED_BODY()

public:
	FHeatHistoryPerPlayMode();
	FHeatHistoryPerPlayMode(EPlayMode PlayMode);

public:
	UPROPERTY(EditAnywhere, SaveGame)
	EPlayMode PlayMode;

	UPROPERTY(EditAnywhere, SaveGame)
	int32 PointsThisHeat;

public:
	void AddHeatPoints(int32 HeatPoints);
	int32 GetHeatPoints() const;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FHeatHistoryElement
{
	GENERATED_BODY()

public:
	FHeatHistoryElement();

	UPROPERTY(EditAnywhere, SaveGame)
	TArray<FHeatHistoryPerPlayMode> HeatValues;
	
	UPROPERTY(EditAnywhere, SaveGame)
	FDateTime DateOfHeatEntry;

	int32 GetHeatPoints() const;
	int32 GetHeatPointsPerPlayMode(EPlayMode PlayMode) const;
	void AddHeatPoints(EPlayMode PlayMode, int32 HeatPoints);
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FHeatHistory 
{
	GENERATED_BODY()

public:
	FHeatHistory();

public:
	UPROPERTY(EditAnywhere, SaveGame)
	TArray<FHeatHistoryElement> HistoryList;

	int32 GetHeatPoints() const;
	EPlayMode HasMostPlayedThisPlayMode() const;
	void AddHeatPoints(EPlayMode PlayMode, int32 HeatPoints);

private:
	void AddNewHeatPoints(EPlayMode PlayMode, int32 HeatPoints);
};
