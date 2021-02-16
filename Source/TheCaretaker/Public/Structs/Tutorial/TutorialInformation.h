/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "TutorialInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FTutorialInformation
{
	GENERATED_BODY()

public:
	FTutorialInformation();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText TextToShow;

};

