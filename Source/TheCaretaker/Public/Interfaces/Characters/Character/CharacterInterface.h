/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API ICharacterInterface
{
	GENERATED_BODY()

public:
	virtual void LeftMouseButton(class ICollectableInterface* &Collectable, bool &bPickupCollected) = 0;
	virtual void RightMouseButton() = 0;
	virtual FVector GetDeathSpawnLocation() const = 0;
	virtual FRotator GetDeathSpawnRotation() const = 0;
	virtual void SetSpeedMultiplier(float SpeedMultiplier) = 0;
	virtual FVector GetLocation() const = 0;
	virtual void IsDilatingTime(float Value) = 0;
};
