/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PauseGameInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPauseGameInterface : public UInterface
{
	GENERATED_BODY()
};

/** Interface is used to Pause and Unpause the game. */
class THECARETAKER_API IPauseGameInterface
{
	GENERATED_BODY()
			
public:
	virtual bool IsPaused() const = 0;
	virtual void SetGamePaused(bool SetGamePaused) = 0;
};
