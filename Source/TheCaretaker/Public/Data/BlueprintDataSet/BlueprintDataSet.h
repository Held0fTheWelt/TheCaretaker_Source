/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/BlueprintData/BlueprintDataType.h"
#include "Engine/DataTable.h"
#include "BlueprintDataSet.generated.h"


UCLASS(BlueprintType, AutoExpandCategories = "DataTable,ImportOptions")
class THECARETAKER_API UBlueprintDataSet : public UDataTable
{
	GENERATED_BODY()

public:
	UBlueprintDataSet();
};