/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/Tutorial/PlayModeTutorialInformation.h"

FPlayModeTutorialInformation::FPlayModeTutorialInformation()
{
	PlayMode = EPlayMode::PM_NONE;
	TitleOnStart = FText();
	CharacterSpeed = 0.f;
	SpiderSpeed = 0.f;
	MonsterHungerTime = 0.f;
	MessagesOfTutorial = TArray<FText>();
}
