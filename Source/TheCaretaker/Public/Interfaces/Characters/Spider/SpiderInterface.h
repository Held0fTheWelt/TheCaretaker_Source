/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpiderInterface.generated.h"

UINTERFACE(MinimalAPI)
class USpiderInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API ISpiderInterface
{
	GENERATED_BODY()

public:
	virtual float SetMoveSpeed(float MoveSpeed) = 0;
	virtual float SetAnimRate(float AnimRate) = 0;
};
