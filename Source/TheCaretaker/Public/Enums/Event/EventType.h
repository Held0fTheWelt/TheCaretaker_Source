/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
	ET_NONE				UMETA(DisplayName = "None"),
	ET_EASTER			UMETA(DisplayName = "Easter"),
	ET_CHRISTMAS		UMETA(DisplayName = "Christmas"),
	ET_HELLOWEEN		UMETA(DisplayName = "Helloween"),
	ET_YVES 			UMETA(DisplayName = "Yves Birthday"),
	ET_OTHER			UMETA(DisplayName = "Other"),
};