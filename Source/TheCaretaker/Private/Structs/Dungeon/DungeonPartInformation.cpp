/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Dungeon/DungeonPartInformation.h"

 
FDungeonPartInformation::FDungeonPartInformation()
{
	PartsWithDifficulty.Empty();

	PartsWithDifficulty.Add(FPartDifficultyInformation());
}

FDungeonPartInformation::FDungeonPartInformation(int32 Number)
{
	PartsWithDifficulty.Empty();

	for (int i = 0; i < Number; i++)
	{
		PartsWithDifficulty.Add(FPartDifficultyInformation());		
	}
}

void FDungeonPartInformation::SetPlayModeClassic()
{
	for (auto PartInformation : PartsWithDifficulty)
	{
		PartInformation.ClassicSettings();
	}
}

void FDungeonPartInformation::SetPlayMode(EPlayMode PlayMode)
{
	for (auto PartInformation : PartsWithDifficulty)
	{
		PartInformation.PlayMode = PlayMode;
	}
}

