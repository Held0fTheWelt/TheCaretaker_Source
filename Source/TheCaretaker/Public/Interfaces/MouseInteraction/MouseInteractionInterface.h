/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MouseInteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMouseInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IMouseInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void LeftMouseButtonClicked(class ICollectableInterface* &CollectableRef) = 0;
};
