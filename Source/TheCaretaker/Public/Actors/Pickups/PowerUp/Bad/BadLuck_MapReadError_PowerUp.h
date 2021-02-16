/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "BadLuck_MapReadError_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_MapReadError_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

private:
	IGameInstanceUIInterface* GameInstance;
};
