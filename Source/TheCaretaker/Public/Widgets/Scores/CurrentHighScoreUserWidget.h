// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "CurrentHighScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UCurrentHighScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCurrentHighScoreUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized();

	//UFUNCTION()
	void SetFocus(int32 FokusIndex, int32 Score, float Time);
	void SetFocusForRank(int32 FokusIndex, int32 Score, float Time, class UTextBlock* Score_Text, class UEditableTextBox* Score_TextBox, class UTextBlock* Score_Score, class UTextBlock* Score_Time);

	void SetValues(int32 Rank, FString Name, int32 Score, float Time);

	UFUNCTION()
	void CommittedName(const FText &Name, ETextCommit::Type Method);

private:
	bool bBlockUpdateCommit;
		
	UFUNCTION()
	void UnblockCommit();

protected:
	UPROPERTY(VisibleAnywhere)
	int32 CurrentRank;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_1_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_1_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_1_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_1_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_2_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_2_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_2_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_2_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_3_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_3_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_3_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_3_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_4_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_4_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_4_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_4_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_5_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_5_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_5_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_5_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_6_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_6_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_6_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_6_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_7_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_7_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_7_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_7_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_8_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_8_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_8_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_8_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_9_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_9_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_9_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_9_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_10_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* Score_10_TextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_10_Score;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score_10_Time;
};
