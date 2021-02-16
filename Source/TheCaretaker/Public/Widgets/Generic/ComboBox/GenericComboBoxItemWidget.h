/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericComboBoxItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UGenericComboBoxItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ComboBox;

public:
	void SetDefaultStrings(TArray<FString> DefaultStrings);
	void SetCurrentIndex(int32 CurrentIndex);
};
