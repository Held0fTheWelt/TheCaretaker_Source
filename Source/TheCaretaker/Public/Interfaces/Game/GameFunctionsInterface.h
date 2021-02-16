/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFunctionsInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameFunctionsInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API IGameFunctionsInterface
{
	GENERATED_BODY()

public:
	virtual void NewGame() = 0;
	virtual void StopGame() = 0;
};
