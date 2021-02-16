/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/Achievement/AchievementDefinition.h"

FAchievementDefinition::FAchievementDefinition()
{
	ImageToShow = nullptr;
	CountToAchieve = 0;
	TypeOfAchievement = EAchievementType::AT_NONE;
}
