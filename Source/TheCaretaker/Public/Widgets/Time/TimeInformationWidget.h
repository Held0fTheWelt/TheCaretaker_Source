/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/TimeSet/TimeSet.h"
#include "TimeInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UTimeInformationWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Hour;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Minute;
	
public:
	void SetTime(const FTimeSet &Time);
};
