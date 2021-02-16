/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EGameSecretsEnum : uint8
{
	GS_NONE				UMETA(DisplayName = "None"),
	GS_PICKUPS			UMETA(DisplayName = "Pickups"),
	GS_MORETHANTHREE	UMETA(DisplayName = "More than Three"),
	GS_PLAYYVESONCE		UMETA(DisplayName = "Play Yves Once"),
	GS_DEEPDIVE			UMETA(DisplayName = "Harder Levels"),
	GS_HIGHSCORE		UMETA(DisplayName = "Points and Score"),
};