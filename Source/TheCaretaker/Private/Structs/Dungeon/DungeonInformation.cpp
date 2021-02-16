/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Dungeon/DungeonInformation.h"

// Add default functionality here for any IDungeonInformation functions that are not pure virtual.
FDungeonInformation::FDungeonInformation()
{
	FPartInformation Level1;
	Level1.PartOfDungeon = EPartInformation::EPI_LEVEL1;
	DungeonParts.Add(Level1);

	FPartInformation Level2;
	Level2.PartOfDungeon = EPartInformation::EPI_LEVEL2;
	DungeonParts.Add(Level2);


	FPartInformation Level3;
	Level3.PartOfDungeon = EPartInformation::EPI_LEVEL3;
	DungeonParts.Add(Level3);

	NameOfDungeon = FName("");
	MapNameOfPart = FName("");

	FModEvent = nullptr;
}