/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MonsterSpawnPointInterface.generated.h"



UINTERFACE(MinimalAPI)
class UMonsterSpawnPointInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IMonsterSpawnPointInterface
{
	GENERATED_BODY()
        	
public:
	virtual void ShowMonster() = 0;
};
