// @Yves Tanas 2020


#include "GenericEditableTextWidget.h"

#include "Components/EditableTextBox.h"

void UGenericEditableTextWidget::SetText(FText TextToShow)
{
	Text->SetText(TextToShow);
}
