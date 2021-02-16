/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Interfaces/Widgets/NoiseBar/NoiseBarWidgetInterface.h"
#include "SilencePowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ASilencePowerUp : public APowerUp
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

private:
	INoiseBarWidgetInterface* NoiseBarInterface;
};
