/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "MultiObjectPickup.h"

#include "Log/GlobalLog.h"

AMultiObjectPickup::AMultiObjectPickup()
{
	GoodPowerUpClasses = TArray<TSubclassOf<APowerUp>>();
	BadPowerUpClasses = TArray<TSubclassOf<APowerUp>>();

	SpawnMethod = EPickupSpawnMethod::PSM_NONE;

	IndexOfGoodPowerUp = 0;
	IndexOfBadPowerUp = 0;
}

void AMultiObjectPickup::SpawnGoodPowerUp()
{
	if (IndexOfGoodPowerUp >= GoodPowerUpClasses.Num())
	{
		LOG_WARNING(RuntimeExecutionLog, "Index too high ! Cannot set Good Power Up.")
	}
	else
	{
		CurrentPowerUpClass = GoodPowerUpClasses[IndexOfGoodPowerUp];
	}
}

void AMultiObjectPickup::SpawnBadPowerUp()
{
	if (IndexOfBadPowerUp >= GoodPowerUpClasses.Num())
	{
		LOG_WARNING(RuntimeExecutionLog, "Index too high ! Cannot set Bad Power Up.")
	}
	else
	{
		CurrentPowerUpClass = BadPowerUpClasses[IndexOfBadPowerUp];
	}
}
