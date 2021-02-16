/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/Pickup/Pickup.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "SingleObjectPickup.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ASingleObjectPickup : public APickup, public IMouseInteractionInterface
{
	GENERATED_BODY()
	
public:
	ASingleObjectPickup();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditInstanceOnly, Category = "PickupActor")
	TSubclassOf<class APowerUp> PowerUpClass;

	UPROPERTY(EditInstanceOnly, Category = "Lock")
	int32 LevelPointsToUnlock;
	
protected:
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef) override;

public:
	void SetSpawnLocation(FVector SpawnLocation);

	virtual void Respawn() override;

	void KillPowerUpActor();
private:
	UPROPERTY(SaveGame)
	FVector SpawnLocation;

	UPROPERTY(SaveGame)
	bool bHasFirstValuesSet;

	IGameInstanceAccessoryInterface* Accessory;
};
