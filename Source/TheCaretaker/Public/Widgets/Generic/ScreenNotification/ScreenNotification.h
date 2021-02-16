/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenNotification.generated.h"

/** Screen Notifications, shown on a TextBlock inside a Widget */
UCLASS()
class THECARETAKER_API UScreenNotification : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// The Widget that shows text notifications
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UMultiLineEditableText* Notification;

	// Sets a new Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void SetTextNotification(FText NewNotification);

	// Clears current Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearTextNotification();

protected:
	virtual void NativeOnInitialized() override;
};
