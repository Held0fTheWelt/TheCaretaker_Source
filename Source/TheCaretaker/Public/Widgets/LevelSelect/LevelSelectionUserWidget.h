/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Widgets/LevelSelector/LevelSelectorWidgetInterface.h"
#include "Structs/Level/LevelInformation.h"
#include "Structs/Achievement/Achievement.h"
#include "Widgets/BackButton/BackButtonUserWidget.h"
#include "Widgets/Input/SButton.h"
#include "LevelSelectionUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ULevelSelectionUserWidget : public UBackButtonUserWidget, public ILevelSelectorWidgetInterface
{
	GENERATED_BODY()

public:
	ULevelSelectionUserWidget(const FObjectInitializer& ObjectInitializer);

public:	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelTitle;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackgroundButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PreviousLevel;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* NextLevel;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot1_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot2_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot3_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot4_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot5_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot6_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot7_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot8_Icon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot9_Icon;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot1_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot2_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot3_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot4_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot5_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot6_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot7_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot8_Frame;
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* Slot9_Frame;

	UPROPERTY(meta = (BindWidget))
	class UImage* Slot1_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot2_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot3_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot4_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot5_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot6_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot7_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot8_Icon_Curtain;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot9_Icon_Curtain;
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot1;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot2;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot3;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot4;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot5;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot6;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot7;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot8;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Panel_Slot9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot1_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_1_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot2_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_2_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot3_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_3_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot4_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_4_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot5_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_5_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot6_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_6_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot7_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_7_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot8_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_8_9;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_3;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_4;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_5;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_6;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_7;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_8;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Slot9_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Button_Slot_9_9;

	UFUNCTION()
	void ShowNextLevel();
	UFUNCTION()
	void ShowPreviousLevel();

	UFUNCTION()
	void Load_Dungeon_Slot_1();
	UFUNCTION()
	void Load_Dungeon_Slot_2();
	UFUNCTION()
	void Load_Dungeon_Slot_3();

	UFUNCTION()
	void Load_Dungeon_Slot_4();
	UFUNCTION()
	void Load_Dungeon_Slot_5();
	UFUNCTION()
	void Load_Dungeon_Slot_6();

	UFUNCTION()
	void Load_Dungeon_Slot_7();
	UFUNCTION()
	void Load_Dungeon_Slot_8();
	UFUNCTION()
	void Load_Dungeon_Slot_9();
	
	UFUNCTION(BlueprintCallable)
	void SetupTextForArrowImage(int32 SlotValue);

protected:
	virtual void NativeConstruct() override;

	virtual void ReturnToParent() override;

	FAchievementLoadIdentifier Achievements;

	int32 CurrentLevel;

	UFUNCTION(BlueprintCallable)
	void UnbindButtons();

private:
	void ShowDifficultySelector(bool Show);

	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_1_Difficulty_9();

	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_2_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_3_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_4_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_5_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_6_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_7_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_8_Difficulty_9();
	
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_1();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_2();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_3();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_4();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_5();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_6();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_7();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_8();
	UFUNCTION()
	void Load_Dungeon_Slot_9_Difficulty_9();

	UFUNCTION()
	void BackgroundButtonClicked();

private:
	void LoadSelectedLevel(int32 LevelIndex, int32 DifficultyIndex, int32 DungeonIndex, int32 PartIndex);
	

private:
	UPROPERTY()
	bool bShowDifficulties_Slot_1;
	UPROPERTY()
	bool bShowDifficulties_Slot_2;
	UPROPERTY()
	bool bShowDifficulties_Slot_3;
	UPROPERTY()
	bool bShowDifficulties_Slot_4;
	UPROPERTY()
	bool bShowDifficulties_Slot_5;
	UPROPERTY()
	bool bShowDifficulties_Slot_6;
	UPROPERTY()
	bool bShowDifficulties_Slot_7;
	UPROPERTY()
	bool bShowDifficulties_Slot_8;
	UPROPERTY()
	bool bShowDifficulties_Slot_9;

	void SetupDifficultySlotButton(UButton* Button, UTextBlock* TextBlock, int32 Slot = 0, int32 Difficulty = 0, bool IsActive = false, bool IsVisible = false);

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSlotAnimation"))
	void PlaySlotAnimation(int32 index, bool Forward);

	UFUNCTION(BlueprintImplementableEvent)
	void ResetAnimationCall(int32 index);

	UFUNCTION(BlueprintCallable)
	void ResetOpenSlots(int32 index);
	
	UFUNCTION(BlueprintCallable)
	virtual void UpdateLevelSelector();

public:
	virtual void ShowParent() override;
};
