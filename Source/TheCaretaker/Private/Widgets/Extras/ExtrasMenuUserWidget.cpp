/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "ExtrasMenuUserWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Structs/Secret/SecretCredential.h"
#include "Widgets/Extras/SecretCredentialsItemUserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Widgets/SBoxPanel.h"

UExtrasMenuUserWidget::UExtrasMenuUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentLevel = 0;
	Count = 0;
	SecretSlogans = TArray<UTextBlock*>();
}

void UExtrasMenuUserWidget::ShowParent()
{
	LOG_WARNING(RuntimeExecutionLog, "ShowParent")
	//UpdateTableData();
	Super::ShowParent();
}

void UExtrasMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AddCredentialsToArray();

	for (auto Credentials : AllCredentials)
	{
		Credentials->SetVisibility(ESlateVisibility::Hidden);
	}

	UpdateTableData();
}

void UExtrasMenuUserWidget::ReturnToParent()
{
	ClearAllData();
	Super::ReturnToParent();
}

void UExtrasMenuUserWidget::ClearAllData()
{
	for (auto Credentials : AllCredentials)
	{
		Credentials->SetCredentialInfos(-1);
		Credentials->SetVisibility(ESlateVisibility::Hidden);
	}

	for (int32 i = 0; i < SecretSlogans.Num(); i++)
	{
		SolvedSecrets->RemoveChild(SecretSlogans[i]);
	}

	SecretSlogans.Empty();
}

void UExtrasMenuUserWidget::AddCredentialsToArray()
{
	AllCredentials.Add(Credentials_1_0);
	AllCredentials.Add(Credentials_1_1);
	AllCredentials.Add(Credentials_1_2);
	AllCredentials.Add(Credentials_1_3);
	AllCredentials.Add(Credentials_1_4);
	AllCredentials.Add(Credentials_1_5);
	AllCredentials.Add(Credentials_1_6);
	AllCredentials.Add(Credentials_1_7);
	AllCredentials.Add(Credentials_1_8);

	AllCredentials.Add(Credentials_2_0);
	AllCredentials.Add(Credentials_2_1);
	AllCredentials.Add(Credentials_2_2);
	AllCredentials.Add(Credentials_2_3);
	AllCredentials.Add(Credentials_2_4);
	AllCredentials.Add(Credentials_2_5);
	AllCredentials.Add(Credentials_2_6);
	AllCredentials.Add(Credentials_2_7);
	AllCredentials.Add(Credentials_2_8);

	AllCredentials.Add(Credentials_3_0);
	AllCredentials.Add(Credentials_3_1);
	AllCredentials.Add(Credentials_3_2);
	AllCredentials.Add(Credentials_3_3);
	AllCredentials.Add(Credentials_3_4);
	AllCredentials.Add(Credentials_3_5);
	AllCredentials.Add(Credentials_3_6);
	AllCredentials.Add(Credentials_3_7);
	AllCredentials.Add(Credentials_3_8);

	AllCredentials.Add(Credentials_4_0);
	AllCredentials.Add(Credentials_4_1);
	AllCredentials.Add(Credentials_4_2);
	AllCredentials.Add(Credentials_4_3);
	AllCredentials.Add(Credentials_4_4);
	AllCredentials.Add(Credentials_4_5);
	AllCredentials.Add(Credentials_4_6);
	AllCredentials.Add(Credentials_4_7);
	AllCredentials.Add(Credentials_4_8);

	AllCredentials.Add(Credentials_5_0);
	AllCredentials.Add(Credentials_5_1);
	AllCredentials.Add(Credentials_5_2);
	AllCredentials.Add(Credentials_5_3);
	AllCredentials.Add(Credentials_5_4);
	AllCredentials.Add(Credentials_5_5);
	AllCredentials.Add(Credentials_5_6);
	AllCredentials.Add(Credentials_5_7);
	AllCredentials.Add(Credentials_5_8);

	AllCredentials.Add(Credentials_6_0);
	AllCredentials.Add(Credentials_6_1);
	AllCredentials.Add(Credentials_6_2);
	AllCredentials.Add(Credentials_6_3);
	AllCredentials.Add(Credentials_6_4);
	AllCredentials.Add(Credentials_6_5);
	AllCredentials.Add(Credentials_6_6);
	AllCredentials.Add(Credentials_6_7);
	AllCredentials.Add(Credentials_6_8);

	AllCredentials.Add(Credentials_7_0);
	AllCredentials.Add(Credentials_7_1);
	AllCredentials.Add(Credentials_7_2);
	AllCredentials.Add(Credentials_7_3);
	AllCredentials.Add(Credentials_7_4);
	AllCredentials.Add(Credentials_7_5);
	AllCredentials.Add(Credentials_7_6);
	AllCredentials.Add(Credentials_7_7);
	AllCredentials.Add(Credentials_7_8);

	AllCredentials.Add(Credentials_8_0);
	AllCredentials.Add(Credentials_8_1);
	AllCredentials.Add(Credentials_8_2);
	AllCredentials.Add(Credentials_8_3);
	AllCredentials.Add(Credentials_8_4);
	AllCredentials.Add(Credentials_8_5);
	AllCredentials.Add(Credentials_8_6);
	AllCredentials.Add(Credentials_8_7);
	AllCredentials.Add(Credentials_8_8);

	AllCredentials.Add(Credentials_9_0);
	AllCredentials.Add(Credentials_9_1);
	AllCredentials.Add(Credentials_9_2);
	AllCredentials.Add(Credentials_9_3);
	AllCredentials.Add(Credentials_9_4);
	AllCredentials.Add(Credentials_9_5);
	AllCredentials.Add(Credentials_9_6);
	AllCredentials.Add(Credentials_9_7);
	AllCredentials.Add(Credentials_9_8);
}

void UExtrasMenuUserWidget::UpdateTableData()
{
	ClearAllData();

	UE_LOG(LogTemp, Warning, TEXT("Count : %d"), Count);
	
	if (GameInstanceAccessor == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
		GameInstanceAccessor = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
		UpdateTableData();
		return;
	}

	if (AllCredentials.Num() > 81)
	{
		AllCredentials.Empty();
		AddCredentialsToArray();
	}

	if (AllCredentials.Num() == 0)
	{
		AddCredentialsToArray();
	}


	TArray<TArray<TArray<FSecretCredential>>> KnownSecretCredentials = GameInstanceAccessor->GetKnownSecretCredentialsByArrays(CurrentLevel);

	if (KnownSecretCredentials.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Known Secret Credentials Array was count 0!")
		return;
	}

	TArray<int32> SolvedSecretSloganIndices = GameInstanceAccessor->GetSolvedSloganIndices();

	for (int32 i = 0; i < KnownSecretCredentials.Num(); i++)
	{
		for (int32 j = 0; j < KnownSecretCredentials[i].Num(); j++)
		{
			for (int32 k = 0; k < KnownSecretCredentials[i][j].Num(); k++)
			{
				AllCredentials[i * 9 + j]->SetCredentialInfos(k, KnownSecretCredentials[i][j][k].Character, KnownSecretCredentials[i][j][k].TextColorCode, KnownSecretCredentials[i][j][k].OutlineColorCode, KnownSecretCredentials[i][j][k].ConnectedSloganIndex, SolvedSecretSloganIndices);
				Count++;
			}			
		}
	}

	TArray<FString> KnownSecretSlogans = GameInstanceAccessor->GetSecretSlogans();
	TArray<int32> SolvedSecretSloganIndicesThisPlayMode = GameInstanceAccessor->GetCurrentSolvedSloganIndices();
	
	LOG_WARNING(RuntimeExecutionLog, "Implement Known Secret Slogans here ! Indices need review...")
	/*for (int32 i = 0; i < SolvedSecretSloganIndicesThisPlayMode.Num(); i++)
	{
		FString KnownSlogan = KnownSecretSlogans[SolvedSecretSloganIndicesThisPlayMode[i]];
		UTextBlock* TextBlock = NewObject<UTextBlock>(UTextBlock::StaticClass());

		if (TextBlock == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not create TextBlock. This shouldn't happen !")
		}
		else
		{
			TextBlock->SetText(FText::FromString(KnownSlogan));
			SolvedSecrets->AddChild(TextBlock);
			SecretSlogans.Add(TextBlock);
		}
	}*/
}

void UExtrasMenuUserWidget::ShowNextLevel()
{
}

void UExtrasMenuUserWidget::ShowPreviousLevel()
{
}
