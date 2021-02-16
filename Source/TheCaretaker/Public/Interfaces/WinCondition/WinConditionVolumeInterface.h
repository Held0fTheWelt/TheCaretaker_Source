/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WinConditionVolumeInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWinConditionVolumeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IWinConditionVolumeInterface
{
	GENERATED_BODY()

public:
	virtual void CallWinConditionUpdate() = 0;
	virtual bool IsInSafeZone() const = 0;
	virtual bool ShouldWaitForEndOfTime() const = 0;
};
