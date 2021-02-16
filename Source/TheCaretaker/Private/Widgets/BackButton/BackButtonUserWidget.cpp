/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/BackButton/BackButtonUserWidget.h"

#include "Components/Button.h"

void UBackButtonUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Back->OnClicked.IsBound()) Back->OnClicked.AddDynamic(this, &UUserWidgetBase::ReturnToParent);
}
