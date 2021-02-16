/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelSelectorWidgetInterface.generated.h"


UINTERFACE(MinimalAPI)
class ULevelSelectorWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/** */
class THECARETAKER_API ILevelSelectorWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void UpdateLevelSelector() = 0;
};
