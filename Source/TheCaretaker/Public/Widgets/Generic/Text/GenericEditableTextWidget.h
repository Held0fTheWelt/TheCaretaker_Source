/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericEditableTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UGenericEditableTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Text;

public:
	void SetText(FText TextToShow);
};
