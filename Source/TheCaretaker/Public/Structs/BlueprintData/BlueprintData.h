/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/BlueprintData/BlueprintDataType.h"
#include "Engine/DataTable.h"
#include "BlueprintData.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FBlueprintData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBlueprintData();

	FBlueprintData(EBlueprintDataType Type);
public:
	UPROPERTY(EditAnywhere)
	EBlueprintDataType DataType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BlueprintTemplate;
};