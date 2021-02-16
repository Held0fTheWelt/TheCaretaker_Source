/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/Collections/CollectionDataType.h"
#include "Engine/DataTable.h"
#include "CollectionDataSet.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FCollectionData
{
	GENERATED_BODY()

public:
	FCollectionData();

	FCollectionData(ECollectionDataType Type);
	
public:
	UPROPERTY(EditAnywhere)
		ECollectionDataType DataType;

	UPROPERTY(EditAnywhere)
	class UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FCollectionDataSet : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCollectionDataSet();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connected Level")
	int32 LevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection Data")
	TArray<FCollectionData> CollectionData;	
};