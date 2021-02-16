/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Dungeon/DungeonSolveInformation.h"
#include "LevelSolveInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FLevelSolveInformation
{
	GENERATED_BODY()

public:
	FLevelSolveInformation();

public:
	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Dungeon Information")
	TArray<FDungeonSolveInformation> Dungeons;
/*
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Information")
	FName NameOfLevel;

	TArray<FDungeonInformation> DungeonsInLevel;
	TArray<FDungeonInformation> GetDungeonsInLevel() const;*/
};