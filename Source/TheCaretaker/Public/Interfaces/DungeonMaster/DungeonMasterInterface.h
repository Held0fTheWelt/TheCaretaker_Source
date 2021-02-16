/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DungeonMasterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDungeonMasterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IDungeonMasterInterface
{
	GENERATED_BODY()
			
public:
	virtual void SetCapsuleRadius(float Radius) = 0;
};
