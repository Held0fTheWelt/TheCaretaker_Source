/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Information/InformationWidget.h"
#include "DebugInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UDebugInformationWidget : public UInformationWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtMonsters;

public:	
	// Sets a new Text Notification
	virtual void SetMostAngryMonster(FText Notification) override;

	// Clears current Text Notification
	virtual void ClearTextMonstersNotification() override;
};
