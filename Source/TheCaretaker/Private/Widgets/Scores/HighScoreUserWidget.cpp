// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "HighScoreUserWidget.h"

#include "Components/TextBlock.h"

void UHighScoreUserWidget::SetRange(int32 LevelIndex, int32 DungeonIndex, int32 DifficultyIndex, int32 PartIndex)
{
	if (LevelIndex == -1)
	{
		Level->SetText(FText::FromString("All"));
		Dungeon->SetText(FText::FromString(""));
		Difficulty->SetText(FText::FromString(""));
		Part->SetText(FText::FromString(""));
	}
	else
	{
		Level->SetText(FText::FromString(FString::FromInt(LevelIndex)));
		Dungeon->SetText(FText::FromString(FString::FromInt(DungeonIndex)));
		Difficulty->SetText(FText::FromString(FString::FromInt(DifficultyIndex)));
		Part->SetText(FText::FromString(FString::FromInt(PartIndex)));
	}
}

void UHighScoreUserWidget::SetValues(int32 Rank, FString Name, int32 Score, float Time)
{
	switch (Rank)
	{
	case 1:
		SetValues(Name, Score, Time, Score_1_Text, Score_1_Score, Score_1_Time);
		break;
	case 2:
		SetValues(Name, Score, Time, Score_2_Text, Score_2_Score, Score_2_Time);
		break;
	case 3:
		SetValues(Name, Score, Time, Score_3_Text, Score_3_Score, Score_3_Time);
		break;
	case 4:
		SetValues(Name, Score, Time, Score_4_Text, Score_4_Score, Score_4_Time);
		break;
	case 5:
		SetValues(Name, Score, Time, Score_5_Text, Score_5_Score, Score_5_Time);
		break;
	case 6:
		SetValues(Name, Score, Time, Score_6_Text, Score_6_Score, Score_6_Time);
		break;
	case 7:
		SetValues(Name, Score, Time, Score_7_Text, Score_7_Score, Score_7_Time);
		break;
	case 8:
		SetValues(Name, Score, Time, Score_8_Text, Score_8_Score, Score_8_Time);
		break;
	case 9:
		SetValues(Name, Score, Time, Score_9_Text, Score_9_Score, Score_9_Time);
		break;
	case 10:
		SetValues(Name, Score, Time, Score_10_Text, Score_10_Score, Score_10_Time);
		break;
	default:
		break;
	}
}

void UHighScoreUserWidget::SetValues(FString Name, int32 Score, float Time, UTextBlock* Text_Name, UTextBlock* Text_Score, UTextBlock* Text_Time)
{
	Text_Name->SetText(FText::FromString(Name));
	Text_Score->SetText(FText::FromString(FString::FromInt(Score)));
	Text_Time->SetText(FText::FromString(FString::FromInt((int32)Time)));
}
