/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/Achievement/Achievement.h"

FLevelAchievementInformation::FLevelAchievementInformation()
{
	Level = 0;
	Dungeon = 0;
	Part = EPartInformation::EPI_NONE;
	AchievedDifficulty = 0;
}

FLevelAchievementInformation::FLevelAchievementInformation(int32 NewLevel, int32 NewDungeon, EPartInformation NewPart)
{
	Level = NewLevel;
	Dungeon = NewDungeon;
	Part = NewPart;
	AchievedDifficulty = 0;
}


FAchieved::FAchieved()
{
	Index = -1;
	bAchieved = false;
	TimeAchieved = FDateTime::MinValue();
}

FAchievementLoadIdentifier::FAchievementLoadIdentifier()
{
	MaxDifficultyAchieved = 0;
	MaxLevelAchieved = 0;
	MaxDungeonAchieved = 0;
	MaxPartAchievedInDungeon = EPartInformation::EPI_NONE;
	LatesMapNameAchieved = FName("Dungeon1");
}

FAchievement::FAchievement(EAchievementType NewAchievementType)
{
	AchievementType = NewAchievementType;
	CurrentCount = 0;
}

FAchievement::FAchievement()
{
	AchievementType = EAchievementType::AT_NONE;
	CurrentCount = 0;
}
