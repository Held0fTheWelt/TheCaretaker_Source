/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Score/TimeToScore.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FTimeToScore::FTimeToScore()
{
	ScoreType = EScoreType::ST_NONE;
	TimeToScore = 0.f;
}
