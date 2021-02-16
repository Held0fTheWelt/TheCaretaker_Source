/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Part/PartDifficultyInformation.h"

// Add default functionality here for any IPartInformation functions that are not pure virtual.
FPartDifficultyInformation::FPartDifficultyInformation()
{
	PartTitleMessage = FText();
	PartEntryMessage = FText();
	NumberOfGarbage = 0;
	NumberOfChests = 0;
	NumberOfTraps = 0;
	NumberOfSpiders = 1;
	PathNumberMax = 1;
	TimeToGetHungry = 0;
	bWaitForEndOfTime = false;
	PlayMode = EPlayMode::PM_DEFAULT;
}

void FPartDifficultyInformation::ClassicSettings()
{
	bWaitForEndOfTime = true;
	PlayMode = EPlayMode::PM_CLASSIC;
}
