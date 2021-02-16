// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UPickupUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPickupAnimation(bool Forward);
};
