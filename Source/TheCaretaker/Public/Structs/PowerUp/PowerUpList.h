/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Engine/DataTable.h"
#include "Enums/PowerUp/PowerUpType.h"
#include "Enums/PowerUp/PowerUpSelection.h"
#include "PowerUpList.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPowerUpList : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPowerUpList();

public:
	UPROPERTY(EditAnywhere)
	EPowerUpType PowerUpType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APowerUp> PowerUp;
	
	UPROPERTY(EditAnywhere)
	int32 SecretSloganIndexBounding;

	UPROPERTY(EditAnywhere)
	EPowerUpSelection SelectionType;
};
