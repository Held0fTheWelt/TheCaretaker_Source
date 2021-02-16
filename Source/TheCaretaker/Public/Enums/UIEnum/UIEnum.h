/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EUIEnum : uint8
{
	UI_MENU		UMETA(DisplayName = "Menu"),
	UI_PAUSE	UMETA(DisplayName = "Pause"),
	UI_GAME		UMETA(DisplayName = "Game")
};