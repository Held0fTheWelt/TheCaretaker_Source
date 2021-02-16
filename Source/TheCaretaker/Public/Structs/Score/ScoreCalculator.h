/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/Score/ScoreType.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "ScoreCalculator.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FScoreCalculatorInformation
{
	GENERATED_BODY()

public:
	FScoreCalculatorInformation();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EScoreType ScoreType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeStarting;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPartInformation> Part;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FScoreCalculator 
{
	GENERATED_BODY()

public:
	FScoreCalculator();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float PickupMultiplicator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SpeedMultiplicator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeMultiplicator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScorePerGarbage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScorePerChest;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScorePerTrap;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScorePerMeat;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 MonsterHungerScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 FinishingScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeForScoreGarbage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeForScoreChest;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeForScoreTrap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DifficultyBonus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 MeatCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 PickupCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FinishTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool BPickupActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FScoreCalculatorInformation> CurrentCalculatorInformation;
public:
	void CalculateDifficultyModifier(int32 Difficulty);

	float GetSpeedBonusModifier(EScoreType ScoreType, float Time, TEnumAsByte<EPartInformation> Part) const;
	float GetTimeBonusModifier(float Time) const;
	float GetPickupBonusModifier() const;
	int32 CalculateScoreAddition(EScoreType ScoreType, float TimeStarting, float TimeEnding, TEnumAsByte<EPartInformation> Part);
	int32 GetMeatBonus() const;
	int32 GetMonsterHungerBonus(int32 MonsterCount, float AverageHunger) const;
	int32 GetFinishBonus(float CurrentTime = 0.f) const;

	void AddScoreTypeInformation(EScoreType ScoreType, float TimeStarting, TEnumAsByte<EPartInformation> Part);
	int32 ReleaseScoreTypeInformation(EScoreType ScoreType, float TimeEnding);
	float CalculateExtraBonus() const;
	void IncrementMeatCount();
	void IncrementPickupCount();
	void SetPickupActive(bool IsActive);
	void RemoveGoldInformation();
	void SetPartOfChest(TEnumAsByte<EPartInformation> Part);
	void SetFinishingTime(float FinishTime);
};