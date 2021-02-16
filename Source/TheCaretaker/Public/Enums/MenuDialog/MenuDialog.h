/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EMenuDialog : uint8
{
	MD_NONE			UMETA(DisplayName = "None selected"),
	MD_OPTIONS		UMETA(DisplayName = "Options Dialog"),
	MS_GENERAL		UMETA(DisplayName = "General Options Dialog"),
	MS_GRAPHICS		UMETA(DisplayName = "Graphics Options Dialog"),
	MS_AUDIO		UMETA(DisplayName = "Audio Options Dialog"),
	MS_LEVELSELECT	UMETA(DisplayName = "LevelSelection Dialog"),
	MS_CREDENTIALS	UMETA(DisplayName = "Credentials Dialog"),
};