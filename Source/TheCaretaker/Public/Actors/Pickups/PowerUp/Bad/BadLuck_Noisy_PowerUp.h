/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "Interfaces/Widgets/NoiseBar/NoiseBarWidgetInterface.h"
#include "Interfaces/Monsters/Feeding/MonsterFeedingInterface.h"
#include "BadLuck_Noisy_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_Noisy_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()

public:
	ABadLuck_Noisy_PowerUp();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, Category = "PowerUps")
	float NoiseModifier;

private:
	INoiseBarWidgetInterface* NoiseBarInterface;
	TArray<IMonsterFeedingInterface*> Monsters;
};
