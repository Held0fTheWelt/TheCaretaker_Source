/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Structs/PlayMode/CharacterSetup.h"
#include "Structs/PlayMode/ClockSetup.h"
#include "Structs/PlayMode/FlagModifier.h"
#include "Structs/PlayMode/SpiderSetup.h"
#include "Structs/PlayMode/XModifier.h"
#include "Engine/DataTable.h"
#include "Structs/Level/LevelSetup.h"
#include "PlayModeModifierInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPlayModeModifierInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPlayModeModifierInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayMode")
	EPlayMode PlayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayMode")
	class USoundBase* GameTypeAudioApplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Hunger")
	float TimeToGetHungryModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup")
	FCharacterSetup CharacterSetup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spider Setup")
	FSpiderSetup SpiderSetup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock Setup")
	FClockSetup ClockModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag Modifier")
	FFlagModifier FlagModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX Modifier")
	FXModifier FXModifier;
};