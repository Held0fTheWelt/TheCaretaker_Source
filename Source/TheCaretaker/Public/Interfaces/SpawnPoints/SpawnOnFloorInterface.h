/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "UObject/Interface.h"
#include "SpawnOnFloorInterface.generated.h"



UINTERFACE(MinimalAPI)
class USpawnOnFloorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API ISpawnOnFloorInterface
{
	GENERATED_BODY()
        	    
public:
	virtual EPartInformation GetPartOfLevel() const = 0;
	virtual FVector GetLocation() const = 0;
};
