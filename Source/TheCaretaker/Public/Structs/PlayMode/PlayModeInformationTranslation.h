/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Engine/DataTable.h"
#include "PlayModeInformationTranslation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPlayModeInformationTranslation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPlayModeInformationTranslation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayMode PlayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Dungeon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Difficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPartInformation> PartInformation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPartInformation> PartOfLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TitleMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SubtitleMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfGarbage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfChests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfTraps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfSpiders;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PathNumberMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> PathSpreadValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToGetHungry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWaitForEndOfTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayMode PlayModeOfPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Secret0Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Secret0Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Secret0SubColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Secret0SloganIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Secret1Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Secret1Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Secret1SubColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Secret1SloganIndex;
};

