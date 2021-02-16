/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "InvisibilityPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AInvisibilityPowerUp : public APowerUp
{
	GENERATED_BODY()
	
public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Power Ups")
	FString PostProcessingVolumeName;
};
