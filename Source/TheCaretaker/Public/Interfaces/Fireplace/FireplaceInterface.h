/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FireplaceInterface.generated.h"

UINTERFACE(MinimalAPI)
class UFireplaceInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API IFireplaceInterface
{
	GENERATED_BODY()

public:
	virtual void AddFireplaceListener() = 0;
};
