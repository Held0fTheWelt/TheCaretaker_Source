/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Score/ScoreMultiplier.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FScoreMultiplier::FScoreMultiplier()
{
	ScoreModifierType = EScoreModifierType::SMT_NONE;
	ModifierValue = 0.f;
}
