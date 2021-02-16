/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/Spawning/SpawnInformationTable.h"


FGarbageSpawnInformation::FGarbageSpawnInformation()
{
	GarbageBlueprint = nullptr;
	LocalRelocation = FVector(0,0,0);
	LocalReScaling = FVector(1, 1, 1);
}

FChestSpawnInformation::FChestSpawnInformation()
{
	ChestBlueprint = nullptr;
	LocalRelocation = FVector(0, 0, 0);
	LocalReScaling = FVector(1, 1, 1);
}

FTrapSpawnInformation::FTrapSpawnInformation()
{
	TrapBlueprint = nullptr;
	LocalRelocation = FVector(0, 0, 0);
	LocalReScaling = FVector(1, 1, 1);
}
FSpiderSpawnInformation::FSpiderSpawnInformation()
{
	SpiderBlueprint = nullptr;
	LocalRelocation = FVector(0, 0, 0);
	LocalReScaling = FVector(1, 1, 1);
}

FSpawnInformationTable::FSpawnInformationTable()
{
}

TArray<FGarbageSpawnInformation> FSpawnInformationTable::GetGarbageInformation() const
{
	return GarbageInformation;
}

TArray<FChestSpawnInformation> FSpawnInformationTable::GetChestInformation() const
{
	return ChestInformation;
}

TArray<FTrapSpawnInformation> FSpawnInformationTable::GetTrapInformation() const
{
	return TrapInformation;
}

TArray<FSpiderSpawnInformation> FSpawnInformationTable::GetSpiderInformation() const
{
	return SpiderInformation;
}
