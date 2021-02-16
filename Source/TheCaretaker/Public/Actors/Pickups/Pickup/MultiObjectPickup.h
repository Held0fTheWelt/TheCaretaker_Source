/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/Pickup/Pickup.h"
#include "Structs/PowerUp/PowerUpList.h"
#include "MultiObjectPickup.generated.h"

UENUM()
enum EPickupSpawnMethod
{
	PSM_NONE        UMETA(DisplayName = "None"),
	PSM_RANDOM      UMETA(DisplayName = "Random"),
	PSM_CONTINUOUS  UMETA(DisplayName = "Continuous"),
};

/**
 * 
 */
UCLASS(Abstract)
class THECARETAKER_API AMultiObjectPickup : public APickup
{
	GENERATED_BODY()

public:
	AMultiObjectPickup();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup | Information")
	class UDataTable* PowerUpDefinitionTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup | Information")
	FPowerUpList PowerUpList;

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	TArray<TSubclassOf<class APowerUp>> GoodPowerUpClasses;

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	TArray<TSubclassOf<class APowerUp>> BadPowerUpClasses;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	TEnumAsByte<EPickupSpawnMethod> SpawnMethod;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	int32 IndexOfGoodPowerUp;
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	int32 IndexOfBadPowerUp;
protected:
	virtual void SpawnGoodPowerUp();
	virtual void SpawnBadPowerUp();
};
