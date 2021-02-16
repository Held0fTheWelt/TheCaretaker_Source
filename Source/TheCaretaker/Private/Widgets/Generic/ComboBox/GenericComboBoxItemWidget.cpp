// @Yves Tanas 2020


#include "Widgets/Generic/ComboBox/GenericComboBoxItemWidget.h"

#include "Components/ComboBoxString.h"

void UGenericComboBoxItemWidget::SetDefaultStrings(TArray<FString> DefaultStrings)
{
	ComboBox->ClearOptions();

	for (auto Default : DefaultStrings)
	{
		ComboBox->AddOption(Default);
	}

	ComboBox->RefreshOptions();
}

void UGenericComboBoxItemWidget::SetCurrentIndex(int32 CurrentIndex)
{
	ComboBox->SetSelectedIndex(CurrentIndex);
}
