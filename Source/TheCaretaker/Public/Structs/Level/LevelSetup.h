/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Level/LevelDungeonInformation.h"
#include "LevelSetup.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FLevelSetup
{
	GENERATED_BODY()

public:
	FLevelSetup();

public:

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TArray<FLevelDungeonInformation> DungeonsInLevel;	

	void SetClassic();
};