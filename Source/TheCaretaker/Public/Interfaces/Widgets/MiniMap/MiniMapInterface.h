/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MiniMapInterface.generated.h"


UINTERFACE(MinimalAPI)
class UMiniMapInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IMiniMapInterface
{
	GENERATED_BODY()

public:
	virtual float GetVectorLength() = 0;
	virtual void UnregisterWidgetInterface(class IActorMarkerWidgetInterface* Marker) = 0;
	
};
