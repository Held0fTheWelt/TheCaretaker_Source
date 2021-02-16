/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Base/UserWidgetBase.h"
#include "PauseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UPauseUserWidget : public UUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Continue;

	UPROPERTY(meta = (BindWidget))
	class UButton* Restart;

	UPROPERTY(meta = (BindWidget))
	class UButton* Options;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UScreenNotification* MainMessage;
	
	UPROPERTY(meta = (BindWidget))
	class UScreenNotification* AdditionalMessage;
};
