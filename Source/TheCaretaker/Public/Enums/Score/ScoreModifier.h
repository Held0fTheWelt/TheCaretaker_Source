/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EScoreModifierType : uint8
{
	SMT_NONE				UMETA(DisplayName = "None"),
	SMT_TIME_BONUS			UMETA(DisplayName = "Time Bonus"),
	SMT_SPEED_BONUS			UMETA(DisplayName = "Speed Bonus"),
	SMT_PICKUP_BONUS		UMETA(DisplayName = "Pickup Bonus"),
};