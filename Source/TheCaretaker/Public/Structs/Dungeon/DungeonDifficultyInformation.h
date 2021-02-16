/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Dungeon/DungeonPartInformation.h"
#include "DungeonDifficultyInformation.generated.h"
USTRUCT(BlueprintType)
struct THECARETAKER_API FDungeonDifficultyInformation
{
	GENERATED_BODY()

public:
	FDungeonDifficultyInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TArray<FDungeonPartInformation> DungeonParts;

	void SetClassic();
};