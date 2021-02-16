/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClockInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClockInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IClockInterface
{
	GENERATED_BODY()
			
public:
	virtual bool IsTimeUp() const = 0;
	virtual float GetCurrentTime() const = 0;
	virtual float GetMaxTime() const = 0;
};
