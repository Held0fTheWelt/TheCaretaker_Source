/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/Achievement/AchievementType.h"
#include "AchievementCountInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAchievementCountInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IAchievementCountInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void CountAchievement(EAchievementType AchievementType) = 0;
};
