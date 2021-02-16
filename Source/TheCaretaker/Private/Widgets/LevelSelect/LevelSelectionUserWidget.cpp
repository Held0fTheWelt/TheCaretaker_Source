/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/LevelSelect/LevelSelectionUserWidget.h"

#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "UI/Button/CustomButton.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/Dungeon/DungeonInformation.h"
#include "Structs/Part/PartInformation.h"
#include "Structs/Level/LevelInformation.h"
#include "States/Game/CaretakerGameState.h"
#include "Styling/SlateTypes.h"

#pragma region Constructor
ULevelSelectionUserWidget::ULevelSelectionUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentLevel = 0;
	bShowDifficulties_Slot_1 = false;
	bShowDifficulties_Slot_2 = false;
	bShowDifficulties_Slot_3 = false;
	bShowDifficulties_Slot_4 = false;
	bShowDifficulties_Slot_5 = false;
	bShowDifficulties_Slot_6 = false;
	bShowDifficulties_Slot_7 = false;
	bShowDifficulties_Slot_8 = false;
	bShowDifficulties_Slot_9 = false;
}
#pragma endregion

#pragma region Native Construct
void ULevelSelectionUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateLevelSelector();	
}
#pragma endregion

void ULevelSelectionUserWidget::ReturnToParent()
{
	ResetOpenSlots(-1);
	ResetAnimationCall(-1);
	Super::ReturnToParent();
}

void ULevelSelectionUserWidget::UnbindButtons()
{
	if (Button_Slot1_1->OnClicked.IsBound()) { Button_Slot1_1->OnClicked.RemoveAll(this); }
	if (Button_Slot2_1->OnClicked.IsBound()) { Button_Slot2_1->OnClicked.RemoveAll(this); }
	if (Button_Slot3_1->OnClicked.IsBound()) { Button_Slot3_1->OnClicked.RemoveAll(this); }
	if (Button_Slot4_1->OnClicked.IsBound()) { Button_Slot4_1->OnClicked.RemoveAll(this); }
	if (Button_Slot5_1->OnClicked.IsBound()) { Button_Slot5_1->OnClicked.RemoveAll(this); }
	if (Button_Slot6_1->OnClicked.IsBound()) { Button_Slot6_1->OnClicked.RemoveAll(this); }
	if (Button_Slot7_1->OnClicked.IsBound()) { Button_Slot7_1->OnClicked.RemoveAll(this); }
	if (Button_Slot8_1->OnClicked.IsBound()) { Button_Slot8_1->OnClicked.RemoveAll(this); }
	if (Button_Slot9_1->OnClicked.IsBound()) { Button_Slot9_1->OnClicked.RemoveAll(this); }
}

#pragma region Show Difficulty Selector
void ULevelSelectionUserWidget::ShowDifficultySelector(bool Show)
{
	if (Show)
	{
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 0, 0, 0))
			{
				Panel_Slot1->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot1->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot1->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot1->RenderOpacity = 0.f;
			}
		}
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 0, 0, 1))
			{
				Panel_Slot2->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot2->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot2->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot2->RenderOpacity = 0.f;
			}
		}
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 0, 0, 2))
			{
				Panel_Slot3->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot3->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot3->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot3->RenderOpacity = 0.f;
			}
		}

		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 1, 0, 0))
			{
				Panel_Slot4->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot4->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot4->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot4->RenderOpacity = 0.f;
			}
		}
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 1, 0, 1))
			{
				Panel_Slot5->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot5->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot5->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot5->RenderOpacity = 0.f;
			}
		}
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 1, 0, 2))
			{
				Panel_Slot6->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot6->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot6->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot6->RenderOpacity = 0.f;
			}
		}

		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 2, 0, 0))
			{
				Panel_Slot7->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot7->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot7->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot7->RenderOpacity = 0.f;
			}
		}
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 2, 0, 1))
			{
				Panel_Slot8->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot8->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot8->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot8->RenderOpacity = 0.f;
			}
		}
		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 2, 0, 2))
			{
				Panel_Slot9->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				Panel_Slot9->RenderOpacity = 1.f;
			}
			else
			{
				Panel_Slot9->SetVisibility(ESlateVisibility::Hidden);
				Panel_Slot9->RenderOpacity = 0.f;
			}
		}

		if (!BackgroundButton->OnClicked.IsBound()) { BackgroundButton->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::BackgroundButtonClicked); }
				

		if (GameInstanceAccessor == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameInstance Accessory Interface was null ! This shouldn't happen !");
		}
		else
		{
			for (int32 i = 0; i < 9; i++)
			{
				int32 CompleteDifficulties = GameInstanceAccessor->GetMaxDifficulties(0, i/3);
				int32 CurrentDifficultyAchieved = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, i / 3, i % 3);
				if (CurrentDifficultyAchieved >= CompleteDifficulties)
				{
					CurrentDifficultyAchieved = CompleteDifficulties - 1;
				}
				UButton* Button = nullptr;
				UTextBlock* TextBlock = nullptr;
				//int Count = CompleteDifficulties - 1;
				int Count = CurrentDifficultyAchieved;
				switch (i)
				{
				case 0:
					for (int32 j = 8; j >= 1; j--)
					{						
						switch (j)
						{
						case 8:
							Button = Button_Slot1_9;
							TextBlock = Text_Button_Slot_1_9;
							break;
						case 7:
							Button = Button_Slot1_8;
							TextBlock = Text_Button_Slot_1_8;
							break;
						case 6:
							Button = Button_Slot1_7;
							TextBlock = Text_Button_Slot_1_7;
							break;
						case 5:
							Button = Button_Slot1_6;
							TextBlock = Text_Button_Slot_1_6;
							break;
						case 4:
							Button = Button_Slot1_5;
							TextBlock = Text_Button_Slot_1_5;
							break;
						case 3:
							Button = Button_Slot1_4;
							TextBlock = Text_Button_Slot_1_4;
							break;
						case 2:
							Button = Button_Slot1_3;
							TextBlock = Text_Button_Slot_1_3;
							break;
						case 1:
							Button = Button_Slot1_2;
							TextBlock = Text_Button_Slot_1_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							//if (Count == 0)
							//{
							//	UE_LOG(LogTemp, Warning, TEXT("Injecting Button %s, slotValue is : %d, difficulty is: %d"), *Button->GetName(), i, Count);
							//}
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if(j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 1:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot2_9;
							TextBlock = Text_Button_Slot_2_9;
							break;
						case 7:
							Button = Button_Slot2_8;
							TextBlock = Text_Button_Slot_2_8;
							break;
						case 6:
							Button = Button_Slot2_7;
							TextBlock = Text_Button_Slot_2_7;
							break;
						case 5:
							Button = Button_Slot2_6;
							TextBlock = Text_Button_Slot_2_6;
							break;
						case 4:
							Button = Button_Slot2_5;
							TextBlock = Text_Button_Slot_2_5;
							break;
						case 3:
							Button = Button_Slot2_4;
							TextBlock = Text_Button_Slot_2_4;
							break;
						case 2:
							Button = Button_Slot2_3;
							TextBlock = Text_Button_Slot_2_3;
							break;
						case 1:
							Button = Button_Slot2_2;
							TextBlock = Text_Button_Slot_2_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 2:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot3_9;
							TextBlock = Text_Button_Slot_3_9;
							break;
						case 7:
							Button = Button_Slot3_8;
							TextBlock = Text_Button_Slot_3_8;
							break;
						case 6:
							Button = Button_Slot3_7;
							TextBlock = Text_Button_Slot_3_7;
							break;
						case 5:
							Button = Button_Slot3_6;
							TextBlock = Text_Button_Slot_3_6;
							break;
						case 4:
							Button = Button_Slot3_5;
							TextBlock = Text_Button_Slot_3_5;
							break;
						case 3:
							Button = Button_Slot3_4;
							TextBlock = Text_Button_Slot_3_4;
							break;
						case 2:
							Button = Button_Slot3_3;
							TextBlock = Text_Button_Slot_3_3;
							break;
						case 1:
							Button = Button_Slot3_2;
							TextBlock = Text_Button_Slot_3_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 3:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot4_9;
							TextBlock = Text_Button_Slot_4_9;
							break;
						case 7:
							Button = Button_Slot4_8;
							TextBlock = Text_Button_Slot_4_8;
							break;
						case 6:
							Button = Button_Slot4_7;
							TextBlock = Text_Button_Slot_4_7;
							break;
						case 5:
							Button = Button_Slot4_6;
							TextBlock = Text_Button_Slot_4_6;
							break;
						case 4:
							Button = Button_Slot4_5;
							TextBlock = Text_Button_Slot_4_5;
							break;
						case 3:
							Button = Button_Slot4_4;
							TextBlock = Text_Button_Slot_4_4;
							break;
						case 2:
							Button = Button_Slot4_3;
							TextBlock = Text_Button_Slot_4_3;
							break;
						case 1:
							Button = Button_Slot4_2;
							TextBlock = Text_Button_Slot_4_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 4:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot5_9;
							TextBlock = Text_Button_Slot_5_9;
							break;
						case 7:
							Button = Button_Slot5_8;
							TextBlock = Text_Button_Slot_5_8;
							break;
						case 6:
							Button = Button_Slot5_7;
							TextBlock = Text_Button_Slot_5_7;
							break;
						case 5:
							Button = Button_Slot5_6;
							TextBlock = Text_Button_Slot_5_6;
							break;
						case 4:
							Button = Button_Slot5_5;
							TextBlock = Text_Button_Slot_5_5;
							break;
						case 3:
							Button = Button_Slot5_4;
							TextBlock = Text_Button_Slot_5_4;
							break;
						case 2:
							Button = Button_Slot5_3;
							TextBlock = Text_Button_Slot_5_3;
							break;
						case 1:
							Button = Button_Slot5_2;
							TextBlock = Text_Button_Slot_5_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 5:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot6_9;
							TextBlock = Text_Button_Slot_6_9;
							break;
						case 7:
							Button = Button_Slot6_8;
							TextBlock = Text_Button_Slot_6_8;
							break;
						case 6:
							Button = Button_Slot6_7;
							TextBlock = Text_Button_Slot_6_7;
							break;
						case 5:
							Button = Button_Slot6_6;
							TextBlock = Text_Button_Slot_6_6;
							break;
						case 4:
							Button = Button_Slot6_5;
							TextBlock = Text_Button_Slot_6_5;
							break;
						case 3:
							Button = Button_Slot6_4;
							TextBlock = Text_Button_Slot_6_4;
							break;
						case 2:
							Button = Button_Slot6_3;
							TextBlock = Text_Button_Slot_6_3;
							break;
						case 1:
							Button = Button_Slot6_2;
							TextBlock = Text_Button_Slot_6_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 6:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot7_9;
							TextBlock = Text_Button_Slot_7_9;
							break;
						case 7:
							Button = Button_Slot7_8;
							TextBlock = Text_Button_Slot_7_8;
							break;
						case 6:
							Button = Button_Slot7_7;
							TextBlock = Text_Button_Slot_7_7;
							break;
						case 5:
							Button = Button_Slot7_6;
							TextBlock = Text_Button_Slot_7_6;
							break;
						case 4:
							Button = Button_Slot7_5;
							TextBlock = Text_Button_Slot_7_5;
							break;
						case 3:
							Button = Button_Slot7_4;
							TextBlock = Text_Button_Slot_7_4;
							break;
						case 2:
							Button = Button_Slot7_3;
							TextBlock = Text_Button_Slot_7_3;
							break;
						case 1:
							Button = Button_Slot7_2;
							TextBlock = Text_Button_Slot_7_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 7:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot8_9;
							TextBlock = Text_Button_Slot_8_9;
							break;
						case 7:
							Button = Button_Slot8_8;
							TextBlock = Text_Button_Slot_8_8;
							break;
						case 6:
							Button = Button_Slot8_7;
							TextBlock = Text_Button_Slot_8_7;
							break;
						case 5:
							Button = Button_Slot8_6;
							TextBlock = Text_Button_Slot_8_6;
							break;
						case 4:
							Button = Button_Slot8_5;
							TextBlock = Text_Button_Slot_8_5;
							break;
						case 3:
							Button = Button_Slot8_4;
							TextBlock = Text_Button_Slot_8_4;
							break;
						case 2:
							Button = Button_Slot8_3;
							TextBlock = Text_Button_Slot_8_3;
							break;
						case 1:
							Button = Button_Slot8_2;
							TextBlock = Text_Button_Slot_8_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				case 8:
					for (int32 j = 8; j >= 1; j--)
					{
						switch (j)
						{
						case 8:
							Button = Button_Slot9_9;
							TextBlock = Text_Button_Slot_9_9;
							break;
						case 7:
							Button = Button_Slot9_8;
							TextBlock = Text_Button_Slot_9_8;
							break;
						case 6:
							Button = Button_Slot9_7;
							TextBlock = Text_Button_Slot_9_7;
							break;
						case 5:
							Button = Button_Slot9_6;
							TextBlock = Text_Button_Slot_9_6;
							break;
						case 4:
							Button = Button_Slot9_5;
							TextBlock = Text_Button_Slot_9_5;
							break;
						case 3:
							Button = Button_Slot9_4;
							TextBlock = Text_Button_Slot_9_4;
							break;
						case 2:
							Button = Button_Slot9_3;
							TextBlock = Text_Button_Slot_9_3;
							break;
						case 1:
							Button = Button_Slot9_2;
							TextBlock = Text_Button_Slot_9_2;
							break;
						default:
							break;
						}

						if (Count >= 0)
						{
							SetupDifficultySlotButton(Button, TextBlock, i, Count, true, true);
						}
						else
						{
							if (j != 0)
								SetupDifficultySlotButton(Button, TextBlock);
						}
						Count--;
					}
					break;
				default:
					break;
				}

				//UE_LOG(LogTemp, Warning, TEXT("Currently Achieved: %d  --- Max Possible: %d"), CurrentDifficultyAchieved, CompleteDifficulties);
				//UE_LOG(LogTemp, Warning, TEXT(""));
			}
		}

		if (!Button_Slot1_1->OnClicked.IsBound()) { Button_Slot1_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_1); }
		if (!Button_Slot2_1->OnClicked.IsBound()) { Button_Slot2_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_1); }
		if (!Button_Slot3_1->OnClicked.IsBound()) { Button_Slot3_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_1); }
		if (!Button_Slot4_1->OnClicked.IsBound()) { Button_Slot4_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_1); }
		if (!Button_Slot5_1->OnClicked.IsBound()) { Button_Slot5_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_1); }
		if (!Button_Slot6_1->OnClicked.IsBound()) { Button_Slot6_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_1); }
		if (!Button_Slot7_1->OnClicked.IsBound()) { Button_Slot7_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_1); }
		if (!Button_Slot8_1->OnClicked.IsBound()) { Button_Slot8_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_1); }
		if (!Button_Slot9_1->OnClicked.IsBound()) { Button_Slot9_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_1); }
	}
	else
	{
		Panel_Slot1->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot1->RenderOpacity = 0.f;
		Panel_Slot2->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot2->RenderOpacity = 0.f;
		Panel_Slot3->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot3->RenderOpacity = 0.f;
		Panel_Slot4->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot4->RenderOpacity = 0.f;
		Panel_Slot5->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot5->RenderOpacity = 0.f;
		Panel_Slot6->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot6->RenderOpacity = 0.f;
		Panel_Slot7->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot7->RenderOpacity = 0.f;
		Panel_Slot8->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot8->RenderOpacity = 0.f;
		Panel_Slot9->SetVisibility(ESlateVisibility::Hidden);
		Panel_Slot9->RenderOpacity = 0.f;
		
		if (BackgroundButton->OnClicked.IsBound()) { BackgroundButton->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::BackgroundButtonClicked); }

		if (Button_Slot1_1->OnClicked.IsBound()) { Button_Slot1_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_1); }
		if (Button_Slot1_2->OnClicked.IsBound()) { Button_Slot1_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_2); }
		if (Button_Slot1_3->OnClicked.IsBound()) { Button_Slot1_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_3); }
		if (Button_Slot1_4->OnClicked.IsBound()) { Button_Slot1_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_4); }
		if (Button_Slot1_5->OnClicked.IsBound()) { Button_Slot1_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_5); }
		if (Button_Slot1_6->OnClicked.IsBound()) { Button_Slot1_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_6); }
		if (Button_Slot1_7->OnClicked.IsBound()) { Button_Slot1_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_7); }
		if (Button_Slot1_8->OnClicked.IsBound()) { Button_Slot1_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_8); }
		if (Button_Slot1_9->OnClicked.IsBound()) { Button_Slot1_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_9); }

		if (Button_Slot2_1->OnClicked.IsBound()) { Button_Slot2_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_1); }
		if (Button_Slot2_2->OnClicked.IsBound()) { Button_Slot2_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_2); }
		if (Button_Slot2_3->OnClicked.IsBound()) { Button_Slot2_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_3); }
		if (Button_Slot2_4->OnClicked.IsBound()) { Button_Slot2_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_4); }
		if (Button_Slot2_5->OnClicked.IsBound()) { Button_Slot2_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_5); }
		if (Button_Slot2_6->OnClicked.IsBound()) { Button_Slot2_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_6); }
		if (Button_Slot2_7->OnClicked.IsBound()) { Button_Slot2_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_7); }
		if (Button_Slot2_8->OnClicked.IsBound()) { Button_Slot2_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_8); }
		if (Button_Slot2_9->OnClicked.IsBound()) { Button_Slot2_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_9); }

		if (Button_Slot3_1->OnClicked.IsBound()) { Button_Slot3_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_1); }
		if (Button_Slot3_2->OnClicked.IsBound()) { Button_Slot3_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_2); }
		if (Button_Slot3_3->OnClicked.IsBound()) { Button_Slot3_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_3); }
		if (Button_Slot3_4->OnClicked.IsBound()) { Button_Slot3_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_4); }
		if (Button_Slot3_5->OnClicked.IsBound()) { Button_Slot3_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_5); }
		if (Button_Slot3_6->OnClicked.IsBound()) { Button_Slot3_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_6); }
		if (Button_Slot3_7->OnClicked.IsBound()) { Button_Slot3_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_7); }
		if (Button_Slot3_8->OnClicked.IsBound()) { Button_Slot3_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_8); }
		if (Button_Slot3_9->OnClicked.IsBound()) { Button_Slot3_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_9); }

		if (Button_Slot4_1->OnClicked.IsBound()) { Button_Slot4_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_1); }
		if (Button_Slot4_2->OnClicked.IsBound()) { Button_Slot4_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_2); }
		if (Button_Slot4_3->OnClicked.IsBound()) { Button_Slot4_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_3); }
		if (Button_Slot4_4->OnClicked.IsBound()) { Button_Slot4_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_4); }
		if (Button_Slot4_5->OnClicked.IsBound()) { Button_Slot4_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_5); }
		if (Button_Slot4_6->OnClicked.IsBound()) { Button_Slot4_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_6); }
		if (Button_Slot4_7->OnClicked.IsBound()) { Button_Slot4_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_7); }
		if (Button_Slot4_8->OnClicked.IsBound()) { Button_Slot4_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_8); }
		if (Button_Slot4_9->OnClicked.IsBound()) { Button_Slot4_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_9); }

		if (Button_Slot5_1->OnClicked.IsBound()) { Button_Slot5_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_1); }
		if (Button_Slot5_2->OnClicked.IsBound()) { Button_Slot5_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_2); }
		if (Button_Slot5_3->OnClicked.IsBound()) { Button_Slot5_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_3); }
		if (Button_Slot5_4->OnClicked.IsBound()) { Button_Slot5_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_4); }
		if (Button_Slot5_5->OnClicked.IsBound()) { Button_Slot5_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_5); }
		if (Button_Slot5_6->OnClicked.IsBound()) { Button_Slot5_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_6); }
		if (Button_Slot5_7->OnClicked.IsBound()) { Button_Slot5_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_7); }
		if (Button_Slot5_8->OnClicked.IsBound()) { Button_Slot5_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_8); }
		if (Button_Slot5_9->OnClicked.IsBound()) { Button_Slot5_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_9); }

		if (Button_Slot6_1->OnClicked.IsBound()) { Button_Slot6_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_1); }
		if (Button_Slot6_2->OnClicked.IsBound()) { Button_Slot6_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_2); }
		if (Button_Slot6_3->OnClicked.IsBound()) { Button_Slot6_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_3); }
		if (Button_Slot6_4->OnClicked.IsBound()) { Button_Slot6_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_4); }
		if (Button_Slot6_5->OnClicked.IsBound()) { Button_Slot6_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_5); }
		if (Button_Slot6_6->OnClicked.IsBound()) { Button_Slot6_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_6); }
		if (Button_Slot6_7->OnClicked.IsBound()) { Button_Slot6_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_7); }
		if (Button_Slot6_8->OnClicked.IsBound()) { Button_Slot6_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_8); }
		if (Button_Slot6_9->OnClicked.IsBound()) { Button_Slot6_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_9); }

		if (Button_Slot7_1->OnClicked.IsBound()) { Button_Slot7_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_1); }
		if (Button_Slot7_2->OnClicked.IsBound()) { Button_Slot7_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_2); }
		if (Button_Slot7_3->OnClicked.IsBound()) { Button_Slot7_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_3); }
		if (Button_Slot7_4->OnClicked.IsBound()) { Button_Slot7_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_4); }
		if (Button_Slot7_5->OnClicked.IsBound()) { Button_Slot7_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_5); }
		if (Button_Slot7_6->OnClicked.IsBound()) { Button_Slot7_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_6); }
		if (Button_Slot7_7->OnClicked.IsBound()) { Button_Slot7_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_7); }
		if (Button_Slot7_8->OnClicked.IsBound()) { Button_Slot7_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_8); }
		if (Button_Slot7_9->OnClicked.IsBound()) { Button_Slot7_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_9); }

		if (Button_Slot8_1->OnClicked.IsBound()) { Button_Slot8_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_1); }
		if (Button_Slot8_2->OnClicked.IsBound()) { Button_Slot8_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_2); }
		if (Button_Slot8_3->OnClicked.IsBound()) { Button_Slot8_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_3); }
		if (Button_Slot8_4->OnClicked.IsBound()) { Button_Slot8_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_4); }
		if (Button_Slot8_5->OnClicked.IsBound()) { Button_Slot8_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_5); }
		if (Button_Slot8_6->OnClicked.IsBound()) { Button_Slot8_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_6); }
		if (Button_Slot8_7->OnClicked.IsBound()) { Button_Slot8_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_7); }
		if (Button_Slot8_8->OnClicked.IsBound()) { Button_Slot8_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_8); }
		if (Button_Slot8_9->OnClicked.IsBound()) { Button_Slot8_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_9); }

		if (Button_Slot9_1->OnClicked.IsBound()) { Button_Slot9_1->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_1); }
		if (Button_Slot9_2->OnClicked.IsBound()) { Button_Slot9_2->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_2); }
		if (Button_Slot9_3->OnClicked.IsBound()) { Button_Slot9_3->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_3); }
		if (Button_Slot9_4->OnClicked.IsBound()) { Button_Slot9_4->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_4); }
		if (Button_Slot9_5->OnClicked.IsBound()) { Button_Slot9_5->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_5); }
		if (Button_Slot9_6->OnClicked.IsBound()) { Button_Slot9_6->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_6); }
		if (Button_Slot9_7->OnClicked.IsBound()) { Button_Slot9_7->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_7); }
		if (Button_Slot9_8->OnClicked.IsBound()) { Button_Slot9_8->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_8); }
		if (Button_Slot9_9->OnClicked.IsBound()) { Button_Slot9_9->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_9); }
	}
}
#pragma endregion

#pragma region Level Switch
void ULevelSelectionUserWidget::ShowNextLevel()
{
	CurrentLevel++;	
	UpdateLevelSelector();
}

void ULevelSelectionUserWidget::ShowPreviousLevel()
{
	CurrentLevel--;
	UpdateLevelSelector();
}
#pragma endregion

#pragma region Load Dungeons
void ULevelSelectionUserWidget::Load_Dungeon_Slot_1()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 0, EPartInformation::EPI_LEVEL1);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 0, EPartInformation::EPI_LEVEL1 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 0, EPartInformation::EPI_LEVEL2);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 0, EPartInformation::EPI_LEVEL2 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 0, EPartInformation::EPI_LEVEL3);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 0, EPartInformation::EPI_LEVEL3 - 1));
	GameInstanceRouter->ShowLoadLevel();
}


void ULevelSelectionUserWidget::Load_Dungeon_Slot_4()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 1, EPartInformation::EPI_LEVEL1);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 1, EPartInformation::EPI_LEVEL1 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 1, EPartInformation::EPI_LEVEL2);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 1, EPartInformation::EPI_LEVEL2 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 1, EPartInformation::EPI_LEVEL3);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 1, EPartInformation::EPI_LEVEL3 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 2, EPartInformation::EPI_LEVEL1);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 2, EPartInformation::EPI_LEVEL1 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 2, EPartInformation::EPI_LEVEL2);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 2, EPartInformation::EPI_LEVEL2 - 1));
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9()
{
	GameInstanceAccessor->SetCurrentDungeonPartInfos(CurrentLevel, 2, EPartInformation::EPI_LEVEL3);
	GameInstanceAccessor->SetCurrentDifficulty(GameInstanceAccessor->CalculateCurrentDifficultyForPart(CurrentLevel, 2, EPartInformation::EPI_LEVEL3 - 1));
	GameInstanceRouter->ShowLoadLevel();
}
#pragma endregion

#pragma region Setup Text For Arrow Image
void ULevelSelectionUserWidget::SetupTextForArrowImage(int32 SlotValue)
{
	int32 CurrentAchievedDifficulty = 0;
	switch (SlotValue)
	{
	case 1:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 0, 0);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot1_1, Text_Button_Slot_1_1, 0, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot1_1, Text_Button_Slot_1_1);
		}
		break;
	case 2:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 0, 1);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot2_1, Text_Button_Slot_2_1, 1, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot2_1, Text_Button_Slot_2_1);
		}
		break;
	case 3:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 0, 2);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot3_1, Text_Button_Slot_3_1, 2, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot3_1, Text_Button_Slot_3_1);
		}
		break;
	case 4:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 1, 0);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot4_1, Text_Button_Slot_4_1, 3, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot4_1, Text_Button_Slot_4_1);
		}
		break;
	case 5:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 1, 1);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot5_1, Text_Button_Slot_5_1, 4, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot5_1, Text_Button_Slot_5_1);
		}
		break;
	case 6:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 1, 2);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot6_1, Text_Button_Slot_6_1, 5, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot6_1, Text_Button_Slot_6_1);
		}
		break;
	case 7:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 2, 0);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot7_1, Text_Button_Slot_7_1, 6, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot7_1, Text_Button_Slot_7_1);
		}
		break;
	case 8:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 2, 1);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot8_1, Text_Button_Slot_8_1, 7, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot8_1, Text_Button_Slot_8_1);
		}
		break;
	case 9:
		CurrentAchievedDifficulty = GameInstanceAccessor->CalculateCurrentDifficultyForPart(0, 2, 2);
		if (CurrentAchievedDifficulty == 9)
		{
			SetupDifficultySlotButton(Button_Slot9_1, Text_Button_Slot_9_1, 8, 0, true, true);
		}
		else
		{
			SetupDifficultySlotButton(Button_Slot9_1, Text_Button_Slot_9_1);
		}
		break;	
	default:
		break;
	}
}
#pragma endregion

#pragma region Load Dungeons Difficulty 1
void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_1()
{
	if (!bShowDifficulties_Slot_1)
	{
		bShowDifficulties_Slot_1 = true;
		PlaySlotAnimation(0, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 0, 1);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_1()
{
	if (!bShowDifficulties_Slot_2)
	{
		LOG_WARNING(RuntimeExecutionLog, "Clicked Slot 2 Diff 1")
		bShowDifficulties_Slot_2 = true;
		PlaySlotAnimation(1, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 0, 2);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_1()
{
	if (!bShowDifficulties_Slot_3)
	{
		bShowDifficulties_Slot_3 = true;
		PlaySlotAnimation(2, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 0, 3);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_1()
{
	if (!bShowDifficulties_Slot_4)
	{
		bShowDifficulties_Slot_4 = true;
		PlaySlotAnimation(3, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 1, 1);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_1()
{
	if (!bShowDifficulties_Slot_5)
	{
		bShowDifficulties_Slot_5 = true;
		PlaySlotAnimation(4, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 1, 2);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_1()
{
	if (!bShowDifficulties_Slot_6)
	{
		bShowDifficulties_Slot_6 = true;
		PlaySlotAnimation(5, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 1, 3);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_1()
{
	if (!bShowDifficulties_Slot_7)
	{
		bShowDifficulties_Slot_7 = true;
		PlaySlotAnimation(6, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 2, 1);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_1()
{
	if (!bShowDifficulties_Slot_8)
	{
		bShowDifficulties_Slot_8 = true;
		PlaySlotAnimation(7, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 2, 2);
	}
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_1()
{
	if (!bShowDifficulties_Slot_9)
	{
		bShowDifficulties_Slot_9 = true;
		PlaySlotAnimation(8, true);
	}
	else
	{
		LoadSelectedLevel(CurrentLevel, 0, 2, 3);
	}
}
#pragma endregion

#pragma region SlotValue 1
void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 0, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 0, 1);
}
#pragma endregion

#pragma region SlotValue 2

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 0, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 0, 2);
}
#pragma endregion

#pragma region SlotValue 3
void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 0, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 0, 3);
}
#pragma endregion

#pragma region SlotValue 4
void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 1, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 1, 1);
}
#pragma endregion

#pragma region SlotValue 5
void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 1, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 1, 2);
}
#pragma endregion

#pragma region SlotValue 6
void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 1, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 1, 3);
}
#pragma endregion

#pragma region SlotValue 7
void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 2, 1);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 2, 1);
}
#pragma endregion

#pragma region SlotValue 8
void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 2, 2);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 2, 2);
}
#pragma endregion

#pragma region SlotValue 9
void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_2()
{
	LoadSelectedLevel(CurrentLevel, 1, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_3()
{
	LoadSelectedLevel(CurrentLevel, 2, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_4()
{
	LoadSelectedLevel(CurrentLevel, 3, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_5()
{
	LoadSelectedLevel(CurrentLevel, 4, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_6()
{
	LoadSelectedLevel(CurrentLevel, 5, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_7()
{
	LoadSelectedLevel(CurrentLevel, 6, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_8()
{
	LoadSelectedLevel(CurrentLevel, 7, 2, 3);
}

void ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_9()
{
	LoadSelectedLevel(CurrentLevel, 8, 2, 3);
}

void ULevelSelectionUserWidget::BackgroundButtonClicked()
{
	ResetOpenSlots(-1);
	ResetAnimationCall(-1);

}

void ULevelSelectionUserWidget::LoadSelectedLevel(int32 Level, int32 DifficultyIndex, int32 DungeonIndex, int32 PartIndex)
{
	ResetOpenSlots(-1);
	ResetAnimationCall(-1);

	GameInstanceAccessor->SetCurrentDungeonPartInfos(Level, DungeonIndex, EPartInformation(PartIndex));
	GameInstanceAccessor->SetCurrentDifficulty(DifficultyIndex);

	//FCurrentProgress CurrentProgress = GameInstanceAccessor->GetCurrentProgress();
	//UE_LOG(LogTemp, Warning, TEXT("Wanting: %d - %d - %d - %d"), Level, DungeonIndex, DifficultyIndex, PartIndex);
	//UE_LOG(LogTemp, Warning, TEXT("Loading: %d - %d - %d - %d"), CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentDifficulty, (int32)CurrentProgress.CurrentPart);
	
	GameInstanceRouter->ShowLoadLevel();
}

void ULevelSelectionUserWidget::SetupDifficultySlotButton(UButton* Button, UTextBlock* TextBlock, int32 SlotValue, int32 Difficulty, bool IsActive, bool IsVisible)
{
	if (Button == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Setup DifficultySlotButton ! Button was null ! This shouldn't happen !");
		return;
	}

	if (TextBlock == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Setup DifficultySlotButton ! TextBlock was null ! This shouldn't happen !");
		return;
	}

	if (IsVisible)
	{
		Button->SetVisibility(ESlateVisibility::Visible);
		TextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
		TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Button->OnClicked.IsBound()) { Button->OnClicked.RemoveAll(this); }

	if (IsVisible )
	{
		Button->bIsEnabled = IsActive;
		TextBlock->SetText(FText::FromString(FString::FromInt(Difficulty + 1)));	
		if (IsActive)
		{
			switch (SlotValue)
			{
			case 0:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 1:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 3:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 4:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 5:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 6:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 7:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_9); }
					break;
				default:
					break;
				}
				break;
			case 8:
				switch (Difficulty)
				{
				case 0:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_1); }
					break;
				case 1:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_2); }
					break;
				case 2:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_3); }
					break;
				case 3:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_4); }
					break;
				case 4:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_5); }
					break;
				case 5:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_6); }
					break;
				case 6:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_7); }
					break;
				case 7:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_8); }
					break;
				case 8:
					if (!Button->OnClicked.IsBound()) { Button->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_9); }
					break;
				default:
					break;
				}
				break;						
			default:
				break;
			}
		}
	}
}

void ULevelSelectionUserWidget::ResetOpenSlots(int32 index)
{
	bShowDifficulties_Slot_1 = false;
	bShowDifficulties_Slot_2 = false;
	bShowDifficulties_Slot_3 = false;
	bShowDifficulties_Slot_4 = false;
	bShowDifficulties_Slot_5 = false;
	bShowDifficulties_Slot_6 = false;
	bShowDifficulties_Slot_7 = false;
	bShowDifficulties_Slot_8 = false;
	bShowDifficulties_Slot_9 = false;

	Button_Slot1_1->OnClicked.RemoveAll(this);
	Button_Slot2_1->OnClicked.RemoveAll(this);
	Button_Slot3_1->OnClicked.RemoveAll(this);
	Button_Slot4_1->OnClicked.RemoveAll(this);
	Button_Slot5_1->OnClicked.RemoveAll(this);
	Button_Slot6_1->OnClicked.RemoveAll(this);
	Button_Slot7_1->OnClicked.RemoveAll(this);
	Button_Slot8_1->OnClicked.RemoveAll(this);
	Button_Slot9_1->OnClicked.RemoveAll(this);

	Button_Slot1_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot2_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot3_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot4_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot5_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot6_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot7_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot8_1->SetVisibility(ESlateVisibility::Visible);
	Button_Slot9_1->SetVisibility(ESlateVisibility::Visible);

	if (!Button_Slot1_1->OnClicked.IsBound()) { Button_Slot1_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1_Difficulty_1); }
	if (!Button_Slot2_1->OnClicked.IsBound()) { Button_Slot2_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2_Difficulty_1); }
	if (!Button_Slot3_1->OnClicked.IsBound()) { Button_Slot3_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3_Difficulty_1); }
	if (!Button_Slot4_1->OnClicked.IsBound()) { Button_Slot4_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4_Difficulty_1); }
	if (!Button_Slot5_1->OnClicked.IsBound()) { Button_Slot5_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5_Difficulty_1); }
	if (!Button_Slot6_1->OnClicked.IsBound()) { Button_Slot6_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6_Difficulty_1); }
	if (!Button_Slot7_1->OnClicked.IsBound()) { Button_Slot7_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7_Difficulty_1); }
	if (!Button_Slot8_1->OnClicked.IsBound()) { Button_Slot8_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8_Difficulty_1); }
	if (!Button_Slot9_1->OnClicked.IsBound()) { Button_Slot9_1->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9_Difficulty_1); }

	switch (index)
	{
	case 1:
		bShowDifficulties_Slot_1 = true;
		break;
	case 2:
		bShowDifficulties_Slot_2 = true;
		break;
	case 3:
		bShowDifficulties_Slot_3 = true;
		break;
	case 4:
		bShowDifficulties_Slot_4 = true;
		break;
	case 5:
		bShowDifficulties_Slot_5 = true;
		break;
	case 6:
		bShowDifficulties_Slot_6 = true;
		break;
	case 7:
		bShowDifficulties_Slot_7 = true;
		break;
	case 8:
		bShowDifficulties_Slot_8 = true;
		break;
	case 9:
		bShowDifficulties_Slot_9 = true;
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Update LevelSelector
void ULevelSelectionUserWidget::UpdateLevelSelector()
{
	if (GameInstanceAccessor == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
	}
	else
	{
		TArray<FLevelInformation>  LevelInformation = GameInstanceAccessor->GetLevelInformation();

		//UE_LOG(LogTemp, Warning, TEXT("CurrentLevels %d"), LevelInformation.Num());

		if (CurrentLevel == 0 && CurrentLevel == LevelInformation.Num() - 1)
		{
			if (PreviousLevel->OnClicked.IsBound())
			{
				PreviousLevel->OnClicked.RemoveAll(this);
			}
			if (NextLevel->OnClicked.IsBound())
			{
				NextLevel->OnClicked.RemoveAll(this);
			}
			PreviousLevel->SetIsEnabled(false);
			NextLevel->SetIsEnabled(false);			
		}
		else if (CurrentLevel == 0)
		{
			if (PreviousLevel->OnClicked.IsBound())
			{
				PreviousLevel->OnClicked.RemoveAll(this);
			}
			if (!NextLevel->OnClicked.IsBound()) NextLevel->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::ShowNextLevel);

			PreviousLevel->SetIsEnabled(false);
			NextLevel->SetIsEnabled(true);
		}		
		else if (CurrentLevel == LevelInformation.Num() - 1)
		{
			if (!PreviousLevel->OnClicked.IsBound()) PreviousLevel->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::ShowPreviousLevel);
			
			if (NextLevel->OnClicked.IsBound())
			{
				NextLevel->OnClicked.RemoveAll(this);
			}

			PreviousLevel->SetIsEnabled(true);
			NextLevel->SetIsEnabled(false);
		}
		else
		{
			if (!PreviousLevel->OnClicked.IsBound()) PreviousLevel->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::ShowPreviousLevel);
			if (!NextLevel->OnClicked.IsBound()) NextLevel->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::ShowNextLevel);

			PreviousLevel->SetIsEnabled(true);
			NextLevel->SetIsEnabled(true);
		}

		if (CurrentLevel == LevelInformation.Num())
		{
			CurrentLevel = LevelInformation.Num() - 1;
		}

		Achievements = GameInstanceAccessor->GetLoadIdentifier();

		if (LevelInformation.Num() > 0)
		{
			LevelTitle->SetText(FText::FromName(LevelInformation[CurrentLevel].NameOfLevel));
			if (LevelInformation[CurrentLevel].DungeonsInLevel.Num() > 0)
			{
					if (GameInstanceAccessor->HasTutorialFinished() && CurrentLevel == 0 || GameInstanceAccessor->HasPartAchieved(CurrentLevel-1,2,0,2))
					{
						Slot1_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[0].DungeonParts[0].PartInformationImage);
						Slot1_Icon->MarkPackageDirty();
						Slot1_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
						if (!Slot1_Frame->OnClicked.IsBound()) Slot1_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1);
						Slot1_Frame->SetButtonColors(true);
					}
					else
					{
						Slot1_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_1);
						Slot1_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						Slot1_Frame->SetButtonColors(false);
					}

					if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 0, 0, 0))
					{
						Slot2_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[0].DungeonParts[1].PartInformationImage);
						Slot2_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
						if (!Slot2_Frame->OnClicked.IsBound()) Slot2_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2);
						Slot2_Frame->SetButtonColors(true);
					}
					else
					{
						Slot2_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_2);
						Slot2_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						Slot2_Frame->SetButtonColors(false);
					}

					if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 0, 0, 1))
					{
						Slot3_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[0].DungeonParts[2].PartInformationImage);
						Slot3_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
						if (!Slot3_Frame->OnClicked.IsBound()) Slot3_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3);
						Slot3_Frame->SetButtonColors(true);
					}
					else
					{
						Slot3_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_3);
						Slot3_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						Slot3_Frame->SetButtonColors(false);
					}
//				}
			UE_LOG(LogTemp, Warning, TEXT("%d , current level %d"), Achievements.MaxLevelAchieved, CurrentLevel);
			//if (Achievements.MaxDungeonAchieved >= 1 && Achievements.MaxLevelAchieved >= CurrentLevel)
			//{
				if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 0, 0, 2))
				{
					Slot4_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[1].DungeonParts[0].PartInformationImage);
					Slot4_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
					if (!Slot4_Frame->OnClicked.IsBound()) Slot4_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4);
					Slot4_Frame->SetButtonColors(true);
					LOG_WARNING(RuntimeExecutionLog, "Part achieved .")
				}
				else
				{
					LOG_WARNING(RuntimeExecutionLog, "Part not achieved yet.")
					Slot4_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_4);
					Slot4_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					Slot4_Frame->SetButtonColors(false);
				}

				if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 1, 0, 0))
				{
					Slot5_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[1].DungeonParts[1].PartInformationImage);
					Slot5_Icon->MarkPackageDirty();
					Slot5_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
					if (!Slot5_Frame->OnClicked.IsBound()) Slot5_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5);
					Slot5_Frame->SetButtonColors(true);
				}
				else
				{
					Slot5_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_5);
					Slot5_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					Slot5_Frame->SetButtonColors(false);
				}
				if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 1, 0, 1))
				{
					Slot6_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[1].DungeonParts[2].PartInformationImage);
					Slot6_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
					if (!Slot6_Frame->OnClicked.IsBound()) Slot6_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6);
					Slot6_Frame->SetButtonColors(true);
				}
				else
				{
					Slot6_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_6);
					Slot6_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					Slot6_Frame->SetButtonColors(false);
				}

			//if (Achievements.MaxDungeonAchieved >= 2 )//&& Achievements.MaxLevelAchieved >= CurrentLevel)
			//{
				if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 1, 0, 2))
				{
					Slot7_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[2].DungeonParts[0].PartInformationImage);
					Slot7_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
					if (!Slot7_Frame->OnClicked.IsBound()) Slot7_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7);
					Slot7_Frame->SetButtonColors(true);
				}
				else
				{
					Slot7_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_7);
					Slot7_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					Slot7_Frame->SetButtonColors(false);
				}

				if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 2, 0, 0))
				{
					Slot8_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[2].DungeonParts[1].PartInformationImage);
					Slot8_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
					if (!Slot8_Frame->OnClicked.IsBound()) Slot8_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8);
					Slot8_Frame->SetButtonColors(true);
				}
				else
				{
					Slot8_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_8);
					Slot8_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					Slot8_Frame->SetButtonColors(false);
				}

				if (GameInstanceAccessor->HasPartAchieved(CurrentLevel, 2, 0, 1))
				{
					Slot9_Icon->SetBrushFromTexture(LevelInformation[CurrentLevel].DungeonsInLevel[2].DungeonParts[2].PartInformationImage);
					Slot9_Icon_Curtain->SetVisibility(ESlateVisibility::Hidden);
					if (!Slot9_Frame->OnClicked.IsBound()) Slot9_Frame->OnClicked.AddDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9);
					Slot9_Frame->SetButtonColors(true);
				}
				else
				{
					Slot9_Frame->OnClicked.RemoveDynamic(this, &ULevelSelectionUserWidget::Load_Dungeon_Slot_9);
					Slot9_Icon_Curtain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					Slot9_Frame->SetButtonColors(false);

				}
			//}
			}

			if (GameInstanceAccessor->GetCurrentLevelPoints() <= 8)
			{
				ShowDifficultySelector(false);
			}
			else
			{
				ShowDifficultySelector(true);
			}
		}
		else
		{
			LOG_WARNING(InitializationLog, "LevelInformation were empty. Cannot open any Level.")
		}
	}
}
#pragma endregion

void ULevelSelectionUserWidget::ShowParent()
{
	UpdateLevelSelector();
	Super::ShowParent();
}