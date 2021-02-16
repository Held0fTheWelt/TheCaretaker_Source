/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnDungeonMasterInterface.generated.h"

UINTERFACE(MinimalAPI)
class USpawnDungeonMasterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API ISpawnDungeonMasterInterface
{
	GENERATED_BODY()
			
public:
	virtual void SpawnChasingDungeonMaster() = 0;
};
