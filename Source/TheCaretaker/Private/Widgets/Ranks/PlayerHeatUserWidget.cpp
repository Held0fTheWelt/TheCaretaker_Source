/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "PlayerHeatUserWidget.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

UPlayerHeatUserWidget::UPlayerHeatUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HeatDefinitionTable = nullptr;
	PlayerTypeDefinitionTable = nullptr;
	HeatDefinitions = TArray<FHeatDefinition>();
	PlayerTypeDefinitions = TArray<FPlayerTypeDefinition>();
}

void UPlayerHeatUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HeatDefinitionTable == nullptr)
	{
		SizeBox->SetVisibility(ESlateVisibility::Hidden);
		SizeBox->SetRenderOpacity(0.f);
		LOG_WARNING(InitializationLog, "HeatDefinitionTable was null. Is it setup in the Widget Blueprint for PlayerHeat ?")
		return;
	}

	if (PlayerTypeDefinitionTable == nullptr)
	{
		SizeBox->SetVisibility(ESlateVisibility::Hidden);
		SizeBox->SetRenderOpacity(0.f);
		LOG_WARNING(InitializationLog, "PlayerTypeDefinitionTable was null. Is it setup in the Widget Blueprint for PlayerHeat ?")
		return;
	}

	ReadInDataTables();

	GameInstanceAccessor = Cast< IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstanceAccessor == nullptr)
	{
		SizeBox->SetVisibility(ESlateVisibility::Hidden);
		SizeBox->SetRenderOpacity(0.f);
	}

	else
	{
		if (GameInstanceAccessor->CompetitionAvailable())
		{
			if (HeatDefinitionTable == nullptr)
			{
				LOG_WARNING(InitializationLog, "RankDefinitionTable not set up in Blueprint!")
				return;
			}

			if (PlayerTypeDefinitionTable == nullptr)
			{
				LOG_WARNING(InitializationLog, "LeagueDefinitionTable not set up in Blueprint!")
				return;
			}

			SizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			SizeBox->SetRenderOpacity(1.f);
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			static const FString ContextString(TEXT("HeatDefinition"));

			TArray<FName> RowNames = HeatDefinitionTable->GetRowNames();
			HeatDefinitions = TArray<FHeatDefinition>();
			for (int32 i = 0; i < RowNames.Num(); i++)
			{
				FHeatDefinition* HeatDefinition = HeatDefinitionTable->FindRow<FHeatDefinition >(RowNames[i], ContextString, true);
				HeatDefinitions.Add(*HeatDefinition);
			}

			QuickSortHeatDefinition(HeatDefinitions, 0, HeatDefinitions.Num() - 1);
			
			static const FString ContextString2(TEXT("PlayerTypeDefinition"));

			RowNames = PlayerTypeDefinitionTable->GetRowNames();
			PlayerTypeDefinitions = TArray<FPlayerTypeDefinition>();
			for (int32 i = 0; i < RowNames.Num(); i++)
			{
				FPlayerTypeDefinition* CurrentPlayerType = PlayerTypeDefinitionTable->FindRow<FPlayerTypeDefinition >(RowNames[i], ContextString, true);
				PlayerTypeDefinitions.Add(*CurrentPlayerType);
			}

			int32 CurrentHeatPoints = GameInstanceAccessor->GetCurrentHeatPoints();

			for (int32 i = 0; i < HeatDefinitions.Num(); i++)
			{
				if (HeatDefinitions[i].HeatPoints > CurrentHeatPoints)
				{
					if (i == 0)
					{
						PlayerHeat->SetText(FText::FromString(HeatDefinitions[0].NameOfHeat));
						return;
					}
					else
					{
						PlayerHeat->SetText(FText::FromString(HeatDefinitions[i - 1].NameOfHeat));
						return;
					}
				}
			}

			EPlayMode MostPlayedPlayMode = GameInstanceAccessor->GetCurrentPreferredPlayMode();

			for (auto PlayModeType : PlayerTypeDefinitions)
			{
				if (PlayModeType.PlayMode == MostPlayedPlayMode)
				{
					PlayerType->SetText(FText::FromString(PlayModeType.PlayerDescription));
					break;
				}
			}
		}
		else
		{
			SizeBox->SetVisibility(ESlateVisibility::Hidden);
			SizeBox->SetRenderOpacity(0.f); 
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPlayerHeatUserWidget::ReadInDataTables()
{
	//if (HeatDefinitionTable == nullptr)
	//{
	//	LOG_WARNING(InitializationLog, "Could not find HeatDefinition Table ! This shouldn't happen !")
	//	return;
	//}

	//check(HeatDefinitionTable->GetRowStruct()->IsChildOf(FHeatDefinition::StaticStruct()));

	//for (const TPair<FName, uint8*>& RowItr : HeatDefinitionTable->GetRowMap())
	//{
	//	const FHeatDefinition* HeatDef = reinterpret_cast<const FHeatDefinition*>(RowItr.Value);		
	//	HeatDefinition.Add(*HeatDef);
	//}

	//
	//if (PlayerTypeDefinitionTable == nullptr)
	//{
	//	LOG_WARNING(InitializationLog, "Could not find PlayerTypeDefinition Table ! This shouldn't happen !")
	//	return;
	//}

	//check(PlayerTypeDefinitionTable->GetRowStruct()->IsChildOf(FPlayerTypeDefinition::StaticStruct()));

	//for (const TPair<FName, uint8*>& RowItr : PlayerTypeDefinitionTable->GetRowMap())
	//{
	//	const FPlayerTypeDefinition* PlayerTypeDef = reinterpret_cast<const FPlayerTypeDefinition*>(RowItr.Value);
	//	PlayerTypeDefinition.Add(*PlayerTypeDef);
	//}
}

void UPlayerHeatUserWidget::QuickSortHeatDefinition(TArray<FHeatDefinition>& RankDefinition, int32 Start, int32 End)
{
	if (Start < End)
	{
		int32 Part_Index = PartitionHeatDefinition(RankDefinition, Start, End);
		QuickSortHeatDefinition(RankDefinition, Start, Part_Index - 1);
		QuickSortHeatDefinition(RankDefinition, Part_Index + 1, End);
	}
}

int32 UPlayerHeatUserWidget::PartitionHeatDefinition(TArray<FHeatDefinition>& HeatDefinition, int32 Start, int32 End)
{
	int32 Pivot = HeatDefinition[End].HeatPoints;

	int32 P_Index = Start;

	FHeatDefinition temp;

	for (int32 i = Start; i < End; i++)
	{
		if (HeatDefinition[i].HeatPoints < Pivot)
		{
			temp = HeatDefinition[i];
			HeatDefinition[i] = HeatDefinition[P_Index];
			HeatDefinition[P_Index] = temp;
			P_Index++;
		}
	}

	temp = HeatDefinition[End];
	HeatDefinition[End] = HeatDefinition[P_Index];
	HeatDefinition[P_Index] = temp;

	return P_Index;
}
