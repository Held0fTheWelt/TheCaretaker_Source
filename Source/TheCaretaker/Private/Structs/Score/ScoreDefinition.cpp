/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Score/ScoreDefinition.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FScoreDefinition::FScoreDefinition()
{
	ScoreName = "";
	ScoreType = EScoreType::ST_NONE;
	ScoreValue = 0;
}
