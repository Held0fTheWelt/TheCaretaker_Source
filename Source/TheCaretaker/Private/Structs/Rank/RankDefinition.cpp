/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Rank/RankDefinition.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FRankDefinition::FRankDefinition()
{
	League = ELeagueType::LD_NONE;
	RankName = TEXT("");
	OutlineColorStrength = 2;
	LevelPointsToReach = 0;

	TextColorCode = FLinearColor::White;
	OutlineColorCode = FLinearColor::Black;
}
