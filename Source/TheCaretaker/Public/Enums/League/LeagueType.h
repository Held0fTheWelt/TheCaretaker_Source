/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELeagueType : uint8
{
	LD_NONE				UMETA(DisplayName = "None"),
	LD_COPPER			UMETA(DisplayName = "Copper"),
	LD_BRONZE			UMETA(DisplayName = "Bronze"),
	LD_SILVER			UMETA(DisplayName = "Silver"),
	LD_GOLD				UMETA(DisplayName = "Gold"),
	LD_PLATIN			UMETA(DisplayName = "Platinum"),
	LD_DIAMOND			UMETA(DisplayName = "Diamond"),
	LD_IMMORTAL			UMETA(DisplayName = "Immortal"),
};