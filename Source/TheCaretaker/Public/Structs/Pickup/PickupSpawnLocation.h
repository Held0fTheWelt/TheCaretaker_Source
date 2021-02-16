/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"

#include "PickupSpawnLocation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPickupSpawnLocation 
{
	GENERATED_BODY()

public:
	FPickupSpawnLocation();

public:
	UPROPERTY(EditAnywhere)
	FName PickupName;
	UPROPERTY(EditAnywhere)
	int32 Level;
	UPROPERTY(EditAnywhere)
	int32 Dungeon;
	UPROPERTY(EditAnywhere)
	int32 Part;
	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;
};
