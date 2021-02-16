/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"
#include "TimeDilationPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATimeDilationPowerUp : public APowerUp
{
	GENERATED_BODY()
	
public:
	ATimeDilationPowerUp();

protected:
	virtual void BeginPlay() override;

protected:
	float DilationValue;
public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

private:
	ICharacterInterface* CharacterInterface;
};
