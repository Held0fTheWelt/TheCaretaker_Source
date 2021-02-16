/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EDayEnum : uint8
{
	DE_NONE		UMETA(DisplayName = "None"),
	DE_SAT		UMETA(DisplayName = "Saturday"),
	DE_SUN		UMETA(DisplayName = "Sunday"),
	DE_MON		UMETA(DisplayName = "Monday"),
	DE_TUE		UMETA(DisplayName = "Tuesday"),
	DE_WED		UMETA(DisplayName = "Wednesday"),
	DE_THU		UMETA(DisplayName = "Thursday"),
	DE_FRI		UMETA(DisplayName = "Friday"),
};