/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayPath : uint8
{
	PP_NONE				UMETA(DisplayName = "None"),
	PP_LINEAR			UMETA(DisplayName = "Playing Continuously"),
	PP_DIFFICULTY		UMETA(DisplayName = "Play into depth of Difficulty"),
	PP_REPETITIVE		UMETA(DisplayName = "Repeating the Level"),
};