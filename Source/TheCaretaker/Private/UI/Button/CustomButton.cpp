/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "UI/Button/CustomButton.h"
#include "Widgets/Input/SButton.h"
#define LOCTEXT_NAMESPACE "UMG"

UCustomButton::UCustomButton()
{

}

#if WITH_EDITOR
const FText UCustomButton::GetPaletteCategory()
{
	return LOCTEXT("","My Custom Button");
}
#endif

void UCustomButton::SetButtonColors(bool IsActive)
{
	if (IsActive)
	{
		SButton::FArguments ButtonDefaults;
		ButtonDefaults.ButtonStyle(&ButtonStyleActive);
		WidgetStyle = *ButtonDefaults._ButtonStyle;
	}
	else
	{
		SButton::FArguments ButtonDefaults;
		ButtonDefaults.ButtonStyle(&ButtonStyleInactive);
		WidgetStyle = *ButtonDefaults._ButtonStyle;
	}
}

#undef LOCTEXT_NAMESPACE