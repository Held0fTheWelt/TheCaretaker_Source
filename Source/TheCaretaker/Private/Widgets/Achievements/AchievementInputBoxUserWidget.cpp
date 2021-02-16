/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "AchievementInputBoxUserWidget.h"

#include "TimerManager.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"


UAchievementInputBoxUserWidget::UAchievementInputBoxUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TimeToShowSecretUnlockedMessage = 3.f;
}

void UAchievementInputBoxUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextBox->OnTextCommitted.AddDynamic(this, &UAchievementInputBoxUserWidget::TestTextCommited);

	GameInstance = Cast<IGameInstanceInterface>(GetGameInstance());

	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast GameInstance !")
	}
}

void UAchievementInputBoxUserWidget::TestTextCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		TextBox->SetText(FText());

		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast GameInstance !")
		}
		else
		{
			GameInstance->CheckSecretMessageTypedIn(Text);
		}

		PlayAnimationInput(false);
	}
}

void UAchievementInputBoxUserWidget::SecretUnlockedMessage(FText NewSecretTitle, FText NewSecretSlogan, FText NewSecretMessage, bool Success)
{
	SecretTitle->SetText(NewSecretTitle);
	SecretSlogan->SetText(NewSecretSlogan);
	SecretMessage->SetText(NewSecretMessage);

	PlayAnimationMessage(true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SecretUnlocked, this, &UAchievementInputBoxUserWidget::HideSecretUnlockedAgain, .1f, false, TimeToShowSecretUnlockedMessage);

	if (Success == true)
	{
		if (SecretUnlockedSound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog,"Secret Unlocked Sound not set in Blueprint")
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SecretUnlockedSound);
		}
	}
	else
	{
		if (SecretUnlockFailSound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog,"Secret Unlock Fail Sound not set in Blueprint")
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SecretUnlockFailSound);
		}
	}
}

void UAchievementInputBoxUserWidget::HideSecretUnlockedAgain()
{
	PlayAnimationMessage(false);
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}
