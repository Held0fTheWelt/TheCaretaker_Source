/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Level/LevelSetup.h"


// Add default functionality here for any ILevelInformation functions that are not pure virtual.
FLevelSetup::FLevelSetup()
{
	DungeonsInLevel = TArray<FLevelDungeonInformation>();
}

void FLevelSetup::SetClassic()
{
	for (auto Dungeon : DungeonsInLevel)
	{
		Dungeon.SetClassic();
	}
}
