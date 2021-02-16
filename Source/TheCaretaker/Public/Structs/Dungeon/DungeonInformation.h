/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Part/PartInformation.h"
#include "DungeonInformation.generated.h"
USTRUCT(BlueprintType)
struct THECARETAKER_API FDungeonInformation
{
	GENERATED_BODY()

public:
	FDungeonInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Information")
	FName NameOfDungeon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	FName MapNameOfPart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Information")
	TArray<FPartInformation> DungeonParts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Information")
	class UFMODEvent* FModEvent;
};