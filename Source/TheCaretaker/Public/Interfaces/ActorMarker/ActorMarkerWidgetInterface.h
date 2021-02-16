/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorMarkerWidgetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UActorMarkerWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IActorMarkerWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void UpdatePosition(FVector PlayerLocation, FRotator PlayerRotation) = 0;
	virtual FVector2D GetCurrentPosition() = 0;
	virtual void SetScaleFactor(float ScaleFactor) = 0;
	virtual void IsHiddenInGame() = 0;
	virtual void AddJitterToMapWidget(bool AddJitter) = 0;
};
