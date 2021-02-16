/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "BadLuck_TurtleMode_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_TurtleMode_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()
	
public:
	ABadLuck_TurtleMode_PowerUp();

	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Power Ups")
	float SpeedMultiplier;
};
