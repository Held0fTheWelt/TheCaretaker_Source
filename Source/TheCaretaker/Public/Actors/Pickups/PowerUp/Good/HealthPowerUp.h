/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "HealthPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AHealthPowerUp : public APowerUp
{
	GENERATED_BODY()
	
public:
	AHealthPowerUp();

	virtual void OnTickPowerUp() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Healing")
	float HealAmount;

private:
	class UHealthComponent* HealthComponent;
};
