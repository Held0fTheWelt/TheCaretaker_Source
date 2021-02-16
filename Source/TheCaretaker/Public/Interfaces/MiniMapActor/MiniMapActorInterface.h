/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MiniMapActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMiniMapActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IMiniMapActorInterface
{
	GENERATED_BODY()
			
public:
	virtual float RegisterActorMarker(class IActorMarkerWidgetInterface* Marker, bool Register) = 0;
	virtual void SetMapFailure(bool HasFailure) = 0;
};
