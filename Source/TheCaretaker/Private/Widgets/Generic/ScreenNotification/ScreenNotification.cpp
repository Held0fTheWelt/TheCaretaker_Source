// @Yves Tanas 2020


#include "Widgets/Generic/ScreenNotification/ScreenNotification.h"

#include "Components/MultiLineEditableText.h"

void UScreenNotification::SetTextNotification(FText NewNotification)
{
	Notification->SetText(NewNotification);
}

void UScreenNotification::ClearTextNotification()
{
	Notification->SetText(FText::FromString(""));
}

void UScreenNotification::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
