/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPowerUpType : uint8
{
	PUT_NONE			UMETA(DisplayName = "None"),
	PUT_GOOD			UMETA(DisplayName = "Good PowerUp"),
	PUT_BAD				UMETA(DisplayName = "Bad PowerUp"),
	PUT_ALL				UMETA(DisplayName = "All")
};