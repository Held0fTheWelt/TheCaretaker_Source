/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Dungeon/DungeonDifficultySolveInformation.h"
#include "DungeonSolveInformation.generated.h"
USTRUCT(BlueprintType)
struct THECARETAKER_API FDungeonSolveInformation
{
	GENERATED_BODY()

public:
	FDungeonSolveInformation();

public:
	UPROPERTY(VisibleAnywhere, SaveGame)
	TArray<FDungeonDifficultySolveInformation> Difficulties;
};