/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "Interfaces/ActorMarker/ActorMarkerWidgetInterface.h"
#include "BadLuck_MapJitter_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_MapJitter_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

private:
	TArray<IActorMarkerWidgetInterface*> MiniMapInterfaces;
};
