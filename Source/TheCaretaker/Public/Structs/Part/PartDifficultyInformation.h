/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Structs/Secret/SecretCredential.h"
#include "PartDifficultyInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPartDifficultyInformation
{
	GENERATED_BODY()

public:
	FPartDifficultyInformation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText PartTitleMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText PartEntryMessage;
	// Level Achievements

	// Number of Garbage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfGarbage;
	// Number of Chests
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfChests;
	// Number of Traps
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfTraps;

	// Number of spiders to spawn here
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfSpiders;
	// Max Path number to spread;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PathNumberMax;
	// Measure to spread spawning to pathnumbers
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> PathSpreadValue;

	// Time to get hungry for the Monster in this part of level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToGetHungry;

	// Only last one in slot counts
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWaitForEndOfTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayMode PlayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSecretCredential> SecretCredentials;

	void ClassicSettings();
};