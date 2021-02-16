/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Structs/Level/LevelInformation.h"
#include "Structs/FMOD/ModEventList.h"
#include "GameInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FGameInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGameInformation();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Information")
	TArray<FLevelInformation> LevelsInGame;
	TArray<FLevelInformation> GetLevelsInGame() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Information")
	FMODEventList FModEventList;
};
