/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Heat/HeatDefinition.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FHeatDefinition::FHeatDefinition()
{
	HeatPoints = 0;
	NameOfHeat = FString("");
	TextColorCode = FLinearColor::White;
	OutlineColorCode = FLinearColor::Black;
}
