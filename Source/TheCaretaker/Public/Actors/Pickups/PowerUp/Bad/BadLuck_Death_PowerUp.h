/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "BadLuck_Death_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_Death_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()


public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;
};
