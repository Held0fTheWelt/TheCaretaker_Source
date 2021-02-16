/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
//#include "Structs/Part/PartDifficultyInformation.h"
#include "DungeonPartSolveInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FDungeonPartSolveInformation
{
	GENERATED_BODY()
public:
	FDungeonPartSolveInformation();

public:
	UPROPERTY(VisibleAnywhere, SaveGame)
	bool bFinished;
};
