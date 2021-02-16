/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GarbageInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGarbageInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API IGarbageInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetSpawnInformationIndex() const = 0;
};
