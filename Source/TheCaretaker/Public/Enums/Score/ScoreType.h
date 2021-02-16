/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EScoreType : uint8
{
	ST_NONE				UMETA(DisplayName = "None"),
	ST_GARBAGE			UMETA(DisplayName = "Garbage"),
	ST_CHEST			UMETA(DisplayName = "Chest"),
	ST_TRAP				UMETA(DisplayName = "Trap"),
	ST_MEAT				UMETA(DisplayName = "Meat"),
	ST_HUNGER			UMETA(DisplayName = "Hunger"),
	ST_FINISH			UMETA(DisplayName = "Finish"),
	ST_FAIL				UMETA(DisplayName = "Fail"),
	ST_SPECIAL			UMETA(DisplayName = "Special"),
};