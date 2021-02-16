/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Dungeon/DungeonDifficultyInformation.h"
#include "LevelDungeonInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FLevelDungeonInformation
{
	GENERATED_BODY()

public:
	FLevelDungeonInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TArray<FDungeonDifficultyInformation> Difficulties;
	TArray<FDungeonDifficultyInformation> GetDifficulties() const;

	void SetClassic();
};