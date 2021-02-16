/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "MODEventList.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FMODEventList
{
	GENERATED_BODY()

public:
	FMODEventList();

public:
	UPROPERTY(EditAnywhere)
	TArray<TAssetPtr<class UFMODEvent>> ListOfTitles;
};