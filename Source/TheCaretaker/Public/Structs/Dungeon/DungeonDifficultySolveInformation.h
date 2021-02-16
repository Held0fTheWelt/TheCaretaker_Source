/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Dungeon/DungeonPartSolveInformation.h"
#include "DungeonDifficultySolveInformation.generated.h"
USTRUCT(BlueprintType)
struct THECARETAKER_API FDungeonDifficultySolveInformation
{
	GENERATED_BODY()

public:
	FDungeonDifficultySolveInformation();

public:
	UPROPERTY(VisibleAnywhere, SaveGame)
	TArray<FDungeonPartSolveInformation> DungeonParts;
};