/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "PlayModeTutorialInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPlayModeTutorialInformation
{
	GENERATED_BODY()

public:
	FPlayModeTutorialInformation();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	EPlayMode PlayMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CharacterSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SpiderSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MonsterHungerTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText TitleOnStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (MultiLine = true))
	TArray<FText> MessagesOfTutorial;
};