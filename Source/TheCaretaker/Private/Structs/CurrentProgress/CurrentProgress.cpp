/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/CurrentProgress/CurrentProgress.h"

FCurrentProgress::FCurrentProgress()
{
	CurrentLevelName = EName::NAME_None;
	CurrentLevel = 0;
	CurrentDungeon = 0;
	CurrentDifficulty = 0;
	CurrentLevelPoints = 0;
	CurrentPart = EPartInformation::EPI_NONE;

}

void FCurrentProgress::SetCurrentLevelName(FName Name)
{
	CurrentLevelName = Name;
}

void FCurrentProgress::SetCurrentLevel(int32 Level)
{
	CurrentLevel = Level;
}

void FCurrentProgress::SetCurrentDungeon(int32 Dungeon)
{
	CurrentDungeon = Dungeon;
}

void FCurrentProgress::SetCurrentPart(EPartInformation Part)
{
	CurrentPart = Part;
}

void FCurrentProgress::SetCurrentDifficulty(int32 Difficulty)
{
	CurrentDifficulty = Difficulty;
}
