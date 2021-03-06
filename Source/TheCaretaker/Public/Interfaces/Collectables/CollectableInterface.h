/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCollectableInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API ICollectableInterface
{
	GENERATED_BODY()

public:
	virtual class AActor* GetActor() = 0;
};
