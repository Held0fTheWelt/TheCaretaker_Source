/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Part/PartDifficultyInformation.h"
#include "DungeonPartInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FDungeonPartInformation
{
	GENERATED_BODY()
public:
	FDungeonPartInformation();
	FDungeonPartInformation(int32 Number);

	void SetPlayModeClassic();
	void SetPlayMode(EPlayMode PlayMode);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPartDifficultyInformation> PartsWithDifficulty;
};
