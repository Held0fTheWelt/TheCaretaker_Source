/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EFMODParameterType : uint8
{
	FMOD_PT_NONE		UMETA(DisplayName = "None"),
	FMOD_PT_MONSTER		UMETA(DisplayName = "Monster"),
	FMOD_PT_HEARTBEAT	UMETA(DisplayName = "Heartbeat"),
	FMOD_PT_TIME		UMETA(DisplayName = "Time"),
	FMOD_PT_TRAP		UMETA(DisplayName = "Trap"),
};