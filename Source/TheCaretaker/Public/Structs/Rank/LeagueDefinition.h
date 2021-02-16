/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/League/LeagueType.h"
#include "LeagueDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FLeagueDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLeagueDefinition();

public:
	UPROPERTY(EditAnywhere)
	ELeagueType League;

	UPROPERTY(EditAnywhere)
	FString LeagueName;

	UPROPERTY(EditAnywhere)
	FLinearColor TextColorCode;
	UPROPERTY(EditAnywhere)
	FLinearColor OutlineColorCode;
	UPROPERTY(EditAnywhere)
	int32 OutlineColorStrength;
};
