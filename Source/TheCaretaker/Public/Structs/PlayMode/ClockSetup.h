/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "ClockSetup.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FClockSetup
{
	GENERATED_BODY()

public:
	FClockSetup();
	
public:
	UPROPERTY(EditAnywhere)
	float ClockModifier;
};