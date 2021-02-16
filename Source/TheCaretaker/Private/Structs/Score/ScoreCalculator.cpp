/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Score/ScoreCalculator.h"

FScoreCalculatorInformation::FScoreCalculatorInformation()
{
	ScoreType = EScoreType::ST_NONE;
	TimeStarting = 0;
	Part = EPartInformation::EPI_NONE;
}

#pragma region Constructor
FScoreCalculator::FScoreCalculator()
{
	PickupMultiplicator = 0.f;
	SpeedMultiplicator = 0.f;
	TimeMultiplicator = 0.f;

	ScorePerGarbage = 0;
	ScorePerChest = 0;
	ScorePerTrap = 0;
	ScorePerMeat = 0;

	MonsterHungerScore = 0;
	FinishingScore = 0;

	TimeForScoreGarbage = 0.f;
	TimeForScoreChest = 0.f;
	TimeForScoreTrap = 0.f;

	DifficultyBonus = 0.f;

	MeatCount = 0;
	PickupCount = 0;
	FinishTime = 0;
	MaxTime = 0;

	CurrentCalculatorInformation = TArray<FScoreCalculatorInformation>();

	BPickupActive = false;
}
#pragma endregion


void FScoreCalculator::CalculateDifficultyModifier(int32 Difficulty)
{
	DifficultyBonus = 1.f + ((float)(Difficulty) / 10.f);
}


#pragma region Speed Bonus Modifier
float FScoreCalculator::GetSpeedBonusModifier(EScoreType ScoreType, float Time, TEnumAsByte<EPartInformation> Part) const
{
	float ReturnValue = 0.f;
	switch (ScoreType)
	{
	case EScoreType::ST_NONE:
		break;
	case EScoreType::ST_GARBAGE:
		if (TimeForScoreGarbage == 0)
		{
			break;
		}
		ReturnValue = SpeedMultiplicator * (1 - (Time / TimeForScoreGarbage * Part));
		return FMath::Clamp(ReturnValue, 0.f, 1.f);
			
	case EScoreType::ST_CHEST:
		if (TimeForScoreChest == 0)
		{
			break;
		}
		ReturnValue = SpeedMultiplicator * (1 - (Time / TimeForScoreChest * Part));
		return FMath::Clamp(ReturnValue, 0.f, 1.f);
	case EScoreType::ST_TRAP:
		if (TimeForScoreTrap == 0)
		{
			break;
		}
		ReturnValue = SpeedMultiplicator * (1 - (Time / TimeForScoreTrap * Part));
		return FMath::Clamp(ReturnValue, 0.f, 1.f);
	default:
		break;
	}
	return 0.0f;
}
#pragma endregion

#pragma region Time Bonus Modifier
float FScoreCalculator::GetTimeBonusModifier(float Time) const
{
	if (MaxTime == 0)
	{
		return 0.f;
	}
	return TimeMultiplicator * (1 - Time / MaxTime);
}
#pragma endregion

#pragma region Pickup Bonus Modifier
float FScoreCalculator::GetPickupBonusModifier() const
{
	if (BPickupActive)
	{
		return PickupMultiplicator;
	}
	else
	{
		return 1.0f;
	}
}
#pragma endregion

#pragma region Calculate Score Addition
int32 FScoreCalculator::CalculateScoreAddition(EScoreType ScoreType, float TimeStarting, float TimeEnding, TEnumAsByte<EPartInformation> Part)
{
	int32 ScoreToAdd = 0;

	switch (ScoreType)
	{
	case EScoreType::ST_GARBAGE:
		ScoreToAdd = ScorePerGarbage;
		break;
	case EScoreType::ST_CHEST:
		ScoreToAdd = ScorePerChest;
		break;
	case EScoreType::ST_TRAP:
		ScoreToAdd = ScorePerTrap;
		break;
	default:
		break;
	}

	//UE_LOG(LogTemp, Warning, TEXT("ScoreToAdd: %d"), ScoreToAdd);
	//UE_LOG(LogTemp, Warning, TEXT("Time Started: %f"), TimeStarting);
	//UE_LOG(LogTemp, Warning, TEXT("Time Ended: %f"), TimeStarting);
	//UE_LOG(LogTemp, Warning, TEXT("Time Bonus: %f"), GetTimeBonusModifier(TimeEnding));
	//UE_LOG(LogTemp, Warning, TEXT("SpeedBonus: %f"), GetSpeedBonusModifier(ScoreType, TimeEnding - TimeStarting));
	//UE_LOG(LogTemp, Warning, TEXT("DifficultyBonus: %f"), DifficultyBonus);
	//UE_LOG(LogTemp, Warning, TEXT("PickupModifier: %f"), GetPickupBonusModifier());
	
	return (ScoreToAdd * (1 + GetTimeBonusModifier(TimeEnding) + GetSpeedBonusModifier(ScoreType, TimeEnding - TimeStarting, Part) + DifficultyBonus)) * GetPickupBonusModifier();
}
#pragma endregion

#pragma region Get Meat Bonus
int32 FScoreCalculator::GetMeatBonus() const
{
	return MeatCount * ScorePerMeat * DifficultyBonus;
}
#pragma endregion

#pragma region Get MonsterHunger Bonus
int32 FScoreCalculator::GetMonsterHungerBonus(int32 MonsterCount, float AverageHunger) const
{
	return MonsterHungerScore * MonsterCount * (1 - AverageHunger) * DifficultyBonus;
}
#pragma endregion

#pragma region Get Finish Bonus
int32 FScoreCalculator::GetFinishBonus(float CurrentTime) const
{
	if (CurrentTime == 0.f)
	{
		CurrentTime = FinishTime;
	}

	if(MaxTime == 0)
	{
		return 0.f;
	}

	return FinishingScore * (1 - (CurrentTime / MaxTime)) * DifficultyBonus;
}
#pragma endregion

void FScoreCalculator::AddScoreTypeInformation(EScoreType ScoreType, float TimeStarting, TEnumAsByte<EPartInformation> Part)
{
	FScoreCalculatorInformation NewInformation = FScoreCalculatorInformation();
	NewInformation.ScoreType = ScoreType;
	NewInformation.TimeStarting =TimeStarting;
	NewInformation.Part = Part;
	CurrentCalculatorInformation.Add(NewInformation);
}

int32 FScoreCalculator::ReleaseScoreTypeInformation(EScoreType ScoreType, float TimeEnding)
{
	int32 ReturnValue = -1000;

	for (int32 i = 0; i < CurrentCalculatorInformation.Num(); i++)
	{
		if (CurrentCalculatorInformation[i].ScoreType == ScoreType)
		{
			ReturnValue = CalculateScoreAddition(ScoreType, CurrentCalculatorInformation[i].TimeStarting, TimeEnding, CurrentCalculatorInformation[i].Part);
			CurrentCalculatorInformation.RemoveAt(i);
			break;
		}
	}

	return ReturnValue;
}

float FScoreCalculator::CalculateExtraBonus() const
{
	return 1.0f + PickupCount * .1f;;
}

void FScoreCalculator::IncrementMeatCount()
{
	MeatCount++;
}

void FScoreCalculator::IncrementPickupCount()
{
	PickupCount++;
}

void FScoreCalculator::SetPickupActive(bool IsActive)
{
	BPickupActive = IsActive;
}

void FScoreCalculator::RemoveGoldInformation()
{
	for (int32 i = CurrentCalculatorInformation.Num() - 1; i >= 0; i--)
	{
		if (CurrentCalculatorInformation[i].ScoreType == EScoreType::ST_CHEST)
		{
			CurrentCalculatorInformation.RemoveAt(i);
		}
	}
}

void FScoreCalculator::SetPartOfChest(TEnumAsByte<EPartInformation> Part)
{
	for (int32 i = CurrentCalculatorInformation.Num() - 1; i >= 0; i--)
	{
		if (CurrentCalculatorInformation[i].ScoreType == EScoreType::ST_CHEST)
		{
			CurrentCalculatorInformation[i].Part = Part;
		}
	}
}

void FScoreCalculator::SetFinishingTime(float NewFinishTime)
{
	if (FinishTime == 0.f)
	{
		FinishTime = NewFinishTime;
	}
}
