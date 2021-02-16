/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Base/UserWidgetBase.h"


#include "Components/Button.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void UUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstanceAccessor = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceRouter = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceUI = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	bShow = true;
}

void UUserWidgetBase::SetParent(ISwitchableWidgetInterface* CurrentParent)
{
	Parent = CurrentParent;
	if (CurrentParent == nullptr)
	{
		LOG_WARNING(RuntimeLog, "Parent for widget was null. This is okay, if it's the parent window, otherwise navigation won't work properly!");
	}
	else {
		Parent->ShowWidget(false);
	}
}

void UUserWidgetBase::ReturnToParent()
{
	if (Parent != nullptr)
	{
		Parent->ShowWidget(true);
		Parent = nullptr;
	}
	RemoveFromParent();
	Destruct();
}

void UUserWidgetBase::ShowParent()
{
	Parent->ShowWidget(true);
}

void UUserWidgetBase::ShowWidget(bool Show)
{
	if (Show)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	bShow = Show;
}