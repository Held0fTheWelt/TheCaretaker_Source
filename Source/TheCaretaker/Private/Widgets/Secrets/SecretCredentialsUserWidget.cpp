/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SecretCredentialsUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "Log/GlobalLog.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/Secret/SecretCredential.h"
#include "Widgets/Secret/SecretCredentialUserWidget.h"

void USecretCredentialsUserWidget::SetCredentials(FString C1, FLinearColor C1TextColor, FLinearColor C1OutlineColor, FString C2, FLinearColor C2TextColor, FLinearColor C2OutlineColor)
{
	FirstNewCredential->SetCredentialInformation(C1, C1TextColor, C1OutlineColor);
	if (C2 == "")
	{
		SecondNewCredential->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SecondNewCredential->SetVisibility(ESlateVisibility::Visible);
		SecondNewCredential->SetCredentialInformation(C2, C2TextColor, C2OutlineColor);
	}
}

void USecretCredentialsUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ITutorialInterface* TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (TutorialGameMode != nullptr)
	{
		return;
	}

	if (SecretCredentialTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Secret Credential Template was null ! Is it setup in the Widget blueprints variable ?")
		return;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());

	if(GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Game Instance was null! This shouldn't happen !")
		return;
	}

	IGameInstanceUIInterface* GameInstanceInterface = Cast<IGameInstanceUIInterface>(GameInstance);

	if(GameInstanceInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not be cast to interface! This shouldn't happen !")
		return;
	}

	TArray<FSecretCredential> KnownCredentials = GameInstanceInterface->GetCredentials();

	UE_LOG(LogTemp, Display, TEXT("Known Credentials: %d"), KnownCredentials.Num());

	if (KnownCredentials.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No known Credentials. Continuing game")
	}
	else
	{
		TArray<int32> KnownIndices = GameInstanceInterface->GetKnownSecretSloganIndices();
		for (auto CredentialInformation : KnownCredentials)
		{
			bool Known = false;
			for (int i = 0; i < KnownIndices.Num(); i++)
			{
				if (CredentialInformation.ConnectedSloganIndex == KnownIndices[i])
				{
					Known = true;
				}
			}

			if (Known == true)
			{
				continue;
			}

			USecretCredentialUserWidget* Credential = CreateWidget<USecretCredentialUserWidget>(GetWorld(), SecretCredentialTemplate);
			AchievedCredentials->AddChild(Credential);

			UHorizontalBoxSlot* CurrentSlot = UWidgetLayoutLibrary::SlotAsHorizontalBoxSlot(Credential);
			CurrentSlot->Padding = FMargin(0, 0, 25, 0);
			CurrentSlot->Size = FSlateChildSize(ESlateSizeRule::Automatic);
			CurrentSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
			CurrentSlot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
			Credential->Slot = CurrentSlot;
			Credential->SetCredentialInformation(CredentialInformation.Character, CredentialInformation.TextColorCode, CredentialInformation.OutlineColorCode);
		}
	}
}
