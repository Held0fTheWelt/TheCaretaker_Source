/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HeatDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FHeatDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FHeatDefinition();

public:
	UPROPERTY(EditAnywhere)
	int32 HeatPoints;

	UPROPERTY(EditAnywhere)
	FString NameOfHeat;	
	
	UPROPERTY(EditAnywhere)
	FLinearColor TextColorCode;

	UPROPERTY(EditAnywhere)
	FLinearColor OutlineColorCode;
};
