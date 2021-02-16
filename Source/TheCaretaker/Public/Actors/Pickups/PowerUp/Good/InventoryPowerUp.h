/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Interfaces/PlayerState/PlayerStateInterface.h"
#include "InventoryPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AInventoryPowerUp : public APowerUp
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

private:
	IPlayerStateInterface* PlayerStateInterface;
};
