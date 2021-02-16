/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Level/LevelDungeonInformation.h"
#include "Structs/Dungeon/DungeonDifficultyInformation.h"

FLevelDungeonInformation::FLevelDungeonInformation()
{
	Difficulties = TArray<FDungeonDifficultyInformation>();
}

TArray<FDungeonDifficultyInformation> FLevelDungeonInformation::GetDifficulties() const
{
	return Difficulties;
}

void FLevelDungeonInformation::SetClassic()
{
	for (auto Difficulty : Difficulties)
	{
		Difficulty.SetClassic();
	}
}
