/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "TimeSet.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FTimeSet
{
	GENERATED_BODY()

public:
	FTimeSet();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Settings")
	uint8 Hour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Settings")
	uint8 Minute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Settings")
	uint8 Seconds;
};

