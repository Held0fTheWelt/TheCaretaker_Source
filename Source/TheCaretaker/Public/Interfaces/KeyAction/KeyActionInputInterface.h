/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputCoreTypes.h"
#include "KeyActionInputInterface.generated.h"

UINTERFACE(MinimalAPI)
class UKeyActionInputInterface : public UInterface
{
	GENERATED_BODY()
};

/** This interface is used by Action Manager to get and talk to the Input Component */
class THECARETAKER_API IKeyActionInputInterface
{
	GENERATED_BODY()
			
public:
	virtual class UInputComponent* GetPlayerInputComponent() const = 0;
	virtual float GetInputAnalogKeyState(FKey Key) const = 0;
	virtual bool IsInputKeyDown(FKey Key) const = 0;
	virtual bool WasInputKeyJustPressed(FKey Key) const = 0;
	virtual bool WasInputKeyJustReleased(FKey Key) const = 0;
};
