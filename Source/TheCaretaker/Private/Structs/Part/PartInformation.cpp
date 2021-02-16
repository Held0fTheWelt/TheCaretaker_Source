/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Part/PartInformation.h"

// Add default functionality here for any IPartInformation functions that are not pure virtual.
FPartInformation::FPartInformation()
{
	PartOfDungeon = EPartInformation::EPI_NONE;
	PartInformationImage = nullptr;

	MapNameOfPart = FName("");
}