// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/Pickup/Pickup.h"
#include "Structs/PowerUp/PowerUpList.h"
#include "RandomBadPickup.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ARandomBadPickup : public APickup
{
	GENERATED_BODY()
	
public:
	ARandomBadPickup();

	virtual void Respawn() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup | Setup")
	class UDataTable* PickupInformation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup | Setup")
	TArray<TSubclassOf<class APowerUp>> PowerUpSelection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<class APowerUp> DeathPowerDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
	float DeathPowerDownProbability;
protected:

	virtual void BeginPlay() override;



private:
	TArray<FPowerUpList> ReadPowerUpInformation();

	virtual void ChooseRandomPowerUp();

	void PullPowerUpInformation(const TArray<FPowerUpList>& PowerUpSelectionList);
};
