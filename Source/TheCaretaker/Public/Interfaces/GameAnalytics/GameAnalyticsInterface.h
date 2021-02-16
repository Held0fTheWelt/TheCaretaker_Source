/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameAnalyticsInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameAnalyticsInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API IGameAnalyticsInterface
{
	GENERATED_BODY()

public:
	virtual void StartGameAnalyticsSession() = 0;
	virtual void StopGameAnalyicisSession() = 0;
	//virtual void NewGame() = 0;
	//virtual void StopGame() = 0;
};
