/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TutorialInterface.generated.h"


UINTERFACE(MinimalAPI)
class UTutorialInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API ITutorialInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetCurrentTutorialIndex() = 0;
	virtual void SetNextIndex() = 0;
	virtual void CommitFalseMessage(FText Message) = 0;
};
