/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "PartInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPartInformation
{
	GENERATED_BODY()

public:
	FPartInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	FName MapNameOfPart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	class UTexture2D* PartInformationImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Part Information")
	TEnumAsByte<EPartInformation> PartOfDungeon;	
};