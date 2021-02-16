/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/Difficulty/DifficultyLevelInformation.h"
FDifficultyLevelInformation::FDifficultyLevelInformation()
{
	NumberOfGarbage = 0;
	NumberOfChests = 0;
	NumberOfTraps = 0;

	TimesToGetHungry.Empty();

	bWaitForEndOfTime = false;
	TimeToSolveInSeconds = 0;
}
