/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SwitchableWidgetInterface.generated.h"

UINTERFACE(MinimalAPI)
class USwitchableWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/** UserWidget, that can be switched to it's parent */
class THECARETAKER_API ISwitchableWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void ShowWidget(bool Show) = 0;
	virtual void SetParent(ISwitchableWidgetInterface* CurrentParent) = 0;
	virtual void ReturnToParent() = 0;
};
