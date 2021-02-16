/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Base/UserWidgetBase.h"
#include "BackButtonUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UBackButtonUserWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Back;


protected:
	virtual void NativeConstruct() override;
};
