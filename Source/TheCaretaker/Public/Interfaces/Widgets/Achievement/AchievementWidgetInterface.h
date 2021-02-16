/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AchievementWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAchievementWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IAchievementWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void SetAchievementInformation(class UTexture2D* Image, int16 Amount, FText Title, FText Description, FText Date) = 0;
};
