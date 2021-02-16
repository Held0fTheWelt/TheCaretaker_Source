/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "Interfaces/Monsters/Feeding/MonsterFeedingInterface.h"
#include "BadLuck_InstantHunger_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_InstantHunger_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Activated(class AActor* OtherActor) override;

private:
	IMonsterFeedingInterface* MonsterInterface;
};
