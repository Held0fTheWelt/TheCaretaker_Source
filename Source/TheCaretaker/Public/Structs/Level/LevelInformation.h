/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Dungeon/DungeonInformation.h"
#include "Engine/DataTable.h"
#include "LevelInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FLevelInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLevelInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Information")
	FName NameOfLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Information")
	TArray<FDungeonInformation> DungeonsInLevel;
	TArray<FDungeonInformation> GetDungeonsInLevel() const;
};