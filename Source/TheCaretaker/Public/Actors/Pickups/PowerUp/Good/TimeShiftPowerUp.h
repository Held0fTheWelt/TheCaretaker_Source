/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "TimeShiftPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATimeShiftPowerUp : public APowerUp
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

private:
	IGameModeInterface* GameModeInterface;
};
