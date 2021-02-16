/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Level/LevelInformation.h"


// Add default functionality here for any ILevelInformation functions that are not pure virtual.
FLevelInformation::FLevelInformation()
{
	FDungeonInformation Dungeon1;
	DungeonsInLevel.Add(Dungeon1);

	NameOfLevel = FName("");
}

TArray<FDungeonInformation> FLevelInformation::GetDungeonsInLevel() const
{
	return DungeonsInLevel;
}
