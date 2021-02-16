/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "StageInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FStageInformation
{
	GENERATED_BODY()

public:
	FStageInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	FText PartTitleMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	FText PartEntryMessage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	class UTexture2D* PartInformationImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	int32 NumberOfGarbage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	int32 NumberOfChests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	int32 NumberOfTraps;
};