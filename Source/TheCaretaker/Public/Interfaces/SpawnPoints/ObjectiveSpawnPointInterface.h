/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/SpawnPointType/SpawnPointType.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "ObjectiveSpawnPointInterface.generated.h"



UINTERFACE(MinimalAPI)
class UObjectiveSpawnPointInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IObjectiveSpawnPointInterface
{
	GENERATED_BODY()
        	
public:
    virtual ESpawnPointType GetSpawnPointType() const = 0;
    virtual FTransform GetCurrentTransform() const = 0;
    virtual EPartInformation GetCurrentPart() const = 0;
    virtual void SetSpawned(bool Spawned) = 0;
    virtual bool GetIsSpawned() const = 0;
};
