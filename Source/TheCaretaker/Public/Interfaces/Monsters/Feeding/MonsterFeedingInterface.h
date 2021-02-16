/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MonsterFeedingInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMonsterFeedingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IMonsterFeedingInterface
{
	GENERATED_BODY()

public:
	virtual void SetFeedingUIWidget(class UMonsterInformationWidget* Widget) = 0;
	virtual void InstantMonsterHunger() = 0;
	virtual void NoisyPickup(bool IsNoisy) = 0;
	virtual float GetAverageHunger() const = 0;
	virtual const float CalculateFinalAverageHunger() = 0;
};
