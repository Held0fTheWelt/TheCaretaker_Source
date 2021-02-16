/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayMode : uint8
{
	PM_NONE				UMETA(DisplayName = "None"),
	PM_DEFAULT			UMETA(DisplayName = "Default"),
	PM_LAZY				UMETA(DisplayName = "Lazy"),
	PM_CRAZY			UMETA(DisplayName = "Crazy"),
	PM_TIME_ATTACK		UMETA(DisplayName = "Time Attack"),
	PM_PLAGUE			UMETA(DisplayName = "Plague"),
	PM_MONSTER_FREEDOM	UMETA(DisplayName = "Monster Freedom"),
	PM_RESURRECT		UMETA(DisplayName = "Resurrect"),
	PM_LAME				UMETA(DisplayName = "Lame"), // The lazy duck mode
	PM_IRREGULAR		UMETA(DisplayName = "Irregular"),
	PM_UNLOCKED			UMETA(DisplayName = "Unlocked"),
	PM_HOPHOP			UMETA(DisplayName = "Hop-Hop Mode"),
	PM_TEST				UMETA(DisplayName = "Test Mode"),
	PM_CLASSIC			UMETA(DisplayName = "Classic"),
	PM_TUTORIAL			UMETA(DisplayName = "Tutorial")
};