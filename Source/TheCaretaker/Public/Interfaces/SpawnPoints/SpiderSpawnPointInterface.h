/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpiderSpawnPointInterface.generated.h"



UINTERFACE(MinimalAPI)
class USpiderSpawnPointInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API ISpiderSpawnPointInterface
{
	GENERATED_BODY()
        	
public:
	virtual TArray<class AConnectedTargetPoint*> GetTargetPoints() const = 0;
	virtual int32 GetPathIndex() const = 0;
	virtual FString GetName() const = 0;
};
