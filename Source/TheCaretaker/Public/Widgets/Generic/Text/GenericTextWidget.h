/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UGenericTextWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text;

public:
	void SetText(FText TextToShow);
};
