/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/League/LeagueType.h"
#include "RankDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FRankDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FRankDefinition();

public:
	UPROPERTY(EditAnywhere)
	ELeagueType League;
	UPROPERTY(EditAnywhere)
	FString RankName;
	UPROPERTY(EditAnywhere)
	FLinearColor TextColorCode;
	UPROPERTY(EditAnywhere)
	FLinearColor OutlineColorCode;	
	UPROPERTY(EditAnywhere)
	int32 OutlineColorStrength;
	UPROPERTY(EditAnywhere)
	int32 LevelPointsToReach;

};
