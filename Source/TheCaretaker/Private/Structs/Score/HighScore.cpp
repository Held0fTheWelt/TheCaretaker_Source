/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Score/HighScore.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FHighScore::FHighScore()
{
	PlayMode = EPlayMode::PM_NONE;
	Level = 0;
	Dungeon = 0;
	Part = 0;
	Difficulty = 0;

	Entries = TArray<FHighScoreEntry>();
}
