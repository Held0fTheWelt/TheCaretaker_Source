/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/Pickup/MultiObjectPickup.h"
#include "RandomMultiObjectPickup.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ARandomMultiObjectPickup : public AMultiObjectPickup
{
	GENERATED_BODY()
	
protected:
	virtual void Respawn() override;

	virtual void SpawnGoodPowerUp() override;
	virtual void SpawnBadPowerUp() override;
};
