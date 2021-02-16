/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "RandomMultiObjectPickup.h"

#include "Log/GlobalLog.h"

void ARandomMultiObjectPickup::Respawn()
{
	if (GoodPowerUpClasses.Num() == 0 && BadPowerUpClasses.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "Good and Bad Power Up Classes count 0. Cannot spawn something")
		return;
	}
	else if (BadPowerUpClasses.Num() == 0)
	{
		SpawnGoodPowerUp();
	}
	else if (GoodPowerUpClasses.Num() == 0)
	{
		SpawnBadPowerUp();
	}
	else
	{
		int32 RandomInt = FMath::RandRange(0, 20);
		if ((bool)(RandomInt % 2))
			SpawnGoodPowerUp();
		else
			SpawnBadPowerUp();
	}

	Super::Respawn();
}

void ARandomMultiObjectPickup::SpawnGoodPowerUp()
{
	IndexOfGoodPowerUp = FMath::RandRange(0, GoodPowerUpClasses.Num()-1);

	Super::SpawnGoodPowerUp();
}

void ARandomMultiObjectPickup::SpawnBadPowerUp()
{
	IndexOfBadPowerUp = FMath::RandRange(1, BadPowerUpClasses.Num() - 1);

	Super::SpawnBadPowerUp();
}
