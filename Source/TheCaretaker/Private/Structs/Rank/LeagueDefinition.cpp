/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Rank/LeagueDefinition.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FLeagueDefinition::FLeagueDefinition()
{
	League = ELeagueType::LD_NONE;
	LeagueName = "";
	TextColorCode = FLinearColor::White;
	OutlineColorCode = FLinearColor::Black;
	OutlineColorStrength = 2;
}
