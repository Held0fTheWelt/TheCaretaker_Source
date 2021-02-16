/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/PlayMode/PlayModeModifierInformation.h"

FPlayModeModifierInformation::FPlayModeModifierInformation()
{
	PlayMode = EPlayMode::PM_NONE;
	TimeToGetHungryModifier = 1.0f;
	GameTypeAudioApplier = nullptr;
}
