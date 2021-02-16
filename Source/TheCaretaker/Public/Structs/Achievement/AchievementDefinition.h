/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/Achievement/AchievementType.h"
#include "Engine/DataTable.h"
#include "AchievementDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FAchievementDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FAchievementDefinition();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	class UTexture2D* ImageToShow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement Count")
	int32 CountToAchieve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	TEnumAsByte<EAchievementType> TypeOfAchievement;
};