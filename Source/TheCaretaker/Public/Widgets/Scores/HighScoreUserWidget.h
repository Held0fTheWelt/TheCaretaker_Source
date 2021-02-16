// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UHighScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Level;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Dungeon;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Difficulty;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Part;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_1_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_2_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_3_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_4_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_5_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_6_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_7_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_8_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_9_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_10_Text;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_1_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_2_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_3_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_4_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_5_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_6_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_7_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_8_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_9_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_10_Score;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_1_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_2_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_3_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_4_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_5_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_6_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_7_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_8_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_9_Time;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_10_Time;

public:
	void SetRange(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part);
	void SetValues(int32 Rank, FString Name, int32 Score, float Time);
	void SetValues(FString Name, int32 Score, float Time, class UTextBlock* Text_Name, class UTextBlock* Text_Score, class UTextBlock* Text_Time);
};
