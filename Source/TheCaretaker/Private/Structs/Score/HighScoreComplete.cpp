/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Score/HighScoreComplete.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FHighScoreComplete::FHighScoreComplete()
{
	PlayMode = EPlayMode::PM_NONE;
	Level = 0;
	Dungeon = 0;
	Part = 0;
	Difficulty = 0;
	Name = "";
	TimeSucceeded = 0.f;
	Score = 0;
	DateOfPlayedScore = FDateTime::MinValue();
	BonusPickups = 0;
}


