/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MarkerWidgetActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMarkerWidgetActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IMarkerWidgetActorInterface
{
	GENERATED_BODY()

public:
	virtual void SetMarkerWidget(class UActorMarkerWidget* MarkerWidget) = 0;
};
