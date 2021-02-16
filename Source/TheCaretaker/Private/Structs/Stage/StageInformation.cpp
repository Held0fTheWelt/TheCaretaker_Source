/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Stage/StageInformation.h"

// Add default functionality here for any IPartInformation functions that are not pure virtual.
FStageInformation::FStageInformation()
{
	PartInformationImage = nullptr;

	NumberOfGarbage = 0;
	NumberOfChests = 0;
	NumberOfTraps = 0;
}