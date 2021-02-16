/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPowerUpSelection : uint8
{
	PUS_NONE				UMETA(DisplayName = "None"),
	PUS_GOOD_SPEED			UMETA(DisplayName = "Speed PowerUp"),
	PUS_GOOD_INVISIBLE		UMETA(DisplayName = "Invisibility PowerUp"),
	PUS_GOOD_SILENCE		UMETA(DisplayName = "Silence PowerUp"),
	PUS_GOOD_CLOCKFREEZE	UMETA(DisplayName = "Clock Freeze PowerUp"),
	PUS_GOOD_INVENTORY		UMETA(DisplayName = "Inventory PowerUp"),
	PUS_GOOD_TIME_DILATION	UMETA(DisplayName = "Time Dilation PowerUp"),
	PUS_GOOD_TIME_SHIFT		UMETA(DisplayName = "Time Shift PowerUp"),
	PUS_GOOD_BONUS_POINTS	UMETA(DisplayName = "Bonus Points PowerUp"),
	PUS_BAD_DEATH			UMETA(DisplayName = "Death PowerDown"),
	PUS_BAD_GARBAGE			UMETA(DisplayName = "Garbage Lost PowerDown"),
	PUS_BAD_GOLD			UMETA(DisplayName = "Gold Lost PowerDown"),
	PUS_BAD_TRAP			UMETA(DisplayName = "Trap Release PowerDown"),
	PUS_BAD_HUNGER			UMETA(DisplayName = "Instant Hunger PowerDown"),
	PUS_BAD_SPEED			UMETA(DisplayName = "Turtle Mode PowerDown"),
	PUS_BAD_SPIDERSPEED		UMETA(DisplayName = "Spider Speedup PowerDown"),
	PUS_BAD_NOUI			UMETA(DisplayName = "No UI PowerDown"),
	PUS_BAD_NOISY			UMETA(DisplayName = "Noise PowerDown"),
	PUS_BAD_ONE_HANDED		UMETA(DisplayName = "One Handed PowerDown"),
	PUS_BAD_MAP_FAIL		UMETA(DisplayName = "Map Fail PowerDown"),
	PUS_BAD_MAP_JITTER		UMETA(DisplayName = "Map Jitter PowerDown"),
	PUS_BAD_MAP_READ_ERROR	UMETA(DisplayName = "Map Read Error PowerDown"),
};