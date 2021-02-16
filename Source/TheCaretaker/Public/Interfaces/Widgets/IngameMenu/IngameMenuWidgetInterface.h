/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IngameMenuWidgetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UIngameMenuWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IIngameMenuWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void HideInformationCall() = 0;
};
