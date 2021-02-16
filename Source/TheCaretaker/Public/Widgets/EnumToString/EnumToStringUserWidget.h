/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnumToStringUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UEnumToStringUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEnumToStringUserWidget(const FObjectInitializer& ObjectInitializer);
public:
	template<typename T>
	FString EnumToString(const FString& enumName, const T value, const FString& defaultValue) const;
	static FString ExpandEnumString(const FString& name, const FString& enumName);
};
