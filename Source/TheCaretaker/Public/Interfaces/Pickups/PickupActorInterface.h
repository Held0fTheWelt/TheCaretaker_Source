/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickupActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IPickupActorInterface
{
	GENERATED_BODY()

public:
	virtual void Activated(class AActor* OtherActor) = 0;
	virtual void Expired() = 0;
	virtual void OnTickPowerUp() = 0;
};
