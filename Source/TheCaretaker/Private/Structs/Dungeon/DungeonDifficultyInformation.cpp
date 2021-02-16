/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Dungeon/DungeonDifficultyInformation.h"
#include "Structs/Dungeon/DungeonPartInformation.h"


// Add default functionality here for any IDungeonInformation functions that are not pure virtual.
FDungeonDifficultyInformation::FDungeonDifficultyInformation()
{
	DungeonParts.Add(FDungeonPartInformation(1));
	DungeonParts.Add(FDungeonPartInformation(2));
	DungeonParts.Add(FDungeonPartInformation(3));
	DungeonParts.SetNum(3, true);
}

void FDungeonDifficultyInformation::SetClassic()
{
	for (auto Part : DungeonParts)
	{
		Part.SetPlayModeClassic();
	}
}
