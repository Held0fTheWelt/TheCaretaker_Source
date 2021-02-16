/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NoiseBarWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNoiseBarWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API INoiseBarWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void NoisePickupBlockingNoise(bool IsBlockingNoise) = 0;
	virtual void NoisyPickup(float NoiseModifier = 1.f) = 0;
};
