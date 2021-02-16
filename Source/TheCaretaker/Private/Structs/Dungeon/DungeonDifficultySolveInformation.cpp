/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Dungeon/DungeonDifficultySolveInformation.h"
#include "Structs/Dungeon/DungeonPartSolveInformation.h"


// Add default functionality here for any IDungeonInformation functions that are not pure virtual.
FDungeonDifficultySolveInformation::FDungeonDifficultySolveInformation()
{
	DungeonParts.Add(FDungeonPartSolveInformation());
	DungeonParts.Add(FDungeonPartSolveInformation());
	DungeonParts.Add(FDungeonPartSolveInformation());
	DungeonParts.SetNum(3, true);
}
