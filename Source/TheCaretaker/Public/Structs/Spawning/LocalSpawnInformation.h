/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "LocalSpawnInformation.generated.h"

#pragma region Local Spawn Information Struct
USTRUCT(BlueprintType)
struct THECARETAKER_API FLocalSpawnInformation
{
	GENERATED_BODY()

public:
	FLocalSpawnInformation();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RangeSpawnOnX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RangeSpawnOnY;
};
#pragma endregion