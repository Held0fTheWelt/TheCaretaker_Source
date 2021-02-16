/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Actors/Spawning/ObjectiveSpawnPointActor.h"
#include "InventoryIconDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FInventoryIconDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FInventoryIconDefinition();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TEnumAsByte<ESpawnPointType> TypeOfImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<class UTexture2D*> InventoryImages;
};
