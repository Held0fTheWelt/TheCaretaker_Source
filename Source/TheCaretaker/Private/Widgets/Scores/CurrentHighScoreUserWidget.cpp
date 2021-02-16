// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "CurrentHighScoreUserWidget.h"

#include "TimerManager.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"


UCurrentHighScoreUserWidget::UCurrentHighScoreUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentRank = 0;
	bBlockUpdateCommit = false;
}

void UCurrentHighScoreUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	bBlockUpdateCommit = false;

	Score_1_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_1_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Score_2_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_2_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Score_3_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_3_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_4_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_4_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_5_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_5_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_6_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_6_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_7_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_7_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_8_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_8_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_9_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_9_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	Score_10_TextBox->SetVisibility(ESlateVisibility::Hidden);
	Score_10_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

}

void UCurrentHighScoreUserWidget::SetFocus(int32 FokusIndex, int32 Score, float Time)
{
	CurrentRank = FokusIndex;
	switch (FokusIndex)
	{
	case 1:
		SetFocusForRank(FokusIndex, Score, Time, Score_1_Text, Score_1_TextBox, Score_1_Score, Score_1_Time);
		break;
	case 2:
		SetFocusForRank(FokusIndex, Score, Time, Score_2_Text, Score_2_TextBox, Score_2_Score, Score_2_Time);
		break;
	case 3:
		SetFocusForRank(FokusIndex, Score, Time, Score_3_Text, Score_3_TextBox, Score_3_Score, Score_3_Time);
		break;
	case 4:
		SetFocusForRank(FokusIndex, Score, Time, Score_4_Text, Score_4_TextBox, Score_4_Score, Score_4_Time);
		break;
	case 5:
		SetFocusForRank(FokusIndex, Score, Time, Score_5_Text, Score_5_TextBox, Score_5_Score, Score_5_Time);
		break;
	case 6:
		SetFocusForRank(FokusIndex, Score, Time, Score_6_Text, Score_6_TextBox, Score_6_Score, Score_6_Time);
		break;
	case 7:
		SetFocusForRank(FokusIndex, Score, Time, Score_7_Text, Score_7_TextBox, Score_7_Score, Score_7_Time);
		break;
	case 8:
		SetFocusForRank(FokusIndex, Score, Time, Score_8_Text, Score_8_TextBox, Score_8_Score, Score_8_Time);
		break;
	case 9:
		SetFocusForRank(FokusIndex, Score, Time, Score_9_Text, Score_9_TextBox, Score_9_Score, Score_9_Time);
		break;
	case 10:
		SetFocusForRank(FokusIndex, Score, Time, Score_10_Text, Score_10_TextBox, Score_10_Score, Score_10_Time);
		break;
	default:
		break;
	}
}

void UCurrentHighScoreUserWidget::SetFocusForRank(int32 FokusIndex, int32 Score, float Time, UTextBlock* Score_Text, UEditableTextBox* Score_TextBox, UTextBlock* Score_Score, UTextBlock* Score_Time)
{
	Score_TextBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Score_Text->SetVisibility(ESlateVisibility::Hidden);
	Score_TextBox->SetUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (Score_TextBox->OnTextCommitted.IsBound())
	{
		Score_TextBox->OnTextCommitted.Clear();
	}
	Score_TextBox->OnTextCommitted.AddDynamic(this, &UCurrentHighScoreUserWidget::CommittedName);
	int32 Minutes = Time / 60;
	int32 Seconds = (int32)Time % 60;
	LOG_WARNING(RuntimeExecutionLog, "Change Time here")
	Score_Time->SetText(FText::FromString(FString::FromInt((int32)Time)));
	Score_Score->SetText(FText::FromString(FString::FromInt(Score)));
}

void UCurrentHighScoreUserWidget::SetValues(int32 Rank, FString Name, int32 Score, float Time)
{
	switch (Rank)
	{
	case 1:
		Score_1_Text->SetText(FText::FromString(Name));
		Score_1_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 2:
		Score_2_Text->SetText(FText::FromString(Name));
		Score_2_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 3:
		Score_3_Text->SetText(FText::FromString(Name));
		Score_3_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 4:
		Score_4_Text->SetText(FText::FromString(Name));
		Score_4_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 5:
		Score_5_Text->SetText(FText::FromString(Name));
		Score_5_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 6:
		Score_6_Text->SetText(FText::FromString(Name));
		Score_6_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 7:
		Score_7_Text->SetText(FText::FromString(Name));
		Score_7_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 8:
		Score_8_Text->SetText(FText::FromString(Name));
		Score_8_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 9:
		Score_9_Text->SetText(FText::FromString(Name));
		Score_9_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	case 10:
		Score_10_Text->SetText(FText::FromString(Name));
		Score_10_Score->SetText(FText::FromString(FString::FromInt(Score)));
		break;
	default:
		break;
	}
}

void UCurrentHighScoreUserWidget::CommittedName(const FText &Name, ETextCommit::Type Method)
{
	if (bBlockUpdateCommit)
	{
		return;
	}

	if (Name.IsEmpty())
	{
		return;
	}

	bBlockUpdateCommit = true;

	switch (CurrentRank)
	{
	case 1:
		Score_1_Text->SetText(Name);
		Score_1_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_1_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 2:
		Score_2_Text->SetText(Name);
		Score_2_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_2_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 3:
		Score_3_Text->SetText(Name);
		Score_3_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_3_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 4:
		Score_4_Text->SetText(Name);
		Score_4_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_4_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 5:
		Score_5_Text->SetText(Name);
		Score_5_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_5_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 6:
		Score_6_Text->SetText(Name);
		Score_6_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_6_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 7:
		Score_7_Text->SetText(Name);
		Score_7_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_7_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 8:
		Score_8_Text->SetText(Name);
		Score_8_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_8_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 9:
		Score_9_Text->SetText(Name);
		Score_9_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_9_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case 10:
		Score_10_Text->SetText(Name);
		Score_10_TextBox->SetVisibility(ESlateVisibility::Hidden);
		Score_10_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	default:
		break;
	}

	LOG_WARNING(RuntimeExecutionLog, "Committing HighScore")

	IGameInstanceUIInterface* GameInstanceUI = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstanceUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
	}
	else
	{
		GameInstanceUI->AddHighScoreEntry(Name.ToString());
		GameInstanceUI->CallHideHighscore();
	}

	FTimerHandle TimerHandle_SmallDelay;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SmallDelay, this, &UCurrentHighScoreUserWidget::UnblockCommit, .5f, false);
}

void UCurrentHighScoreUserWidget::UnblockCommit()
{
	bBlockUpdateCommit = false;
}
