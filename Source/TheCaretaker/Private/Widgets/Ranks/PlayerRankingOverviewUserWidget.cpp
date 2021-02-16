/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "PlayerRankingOverviewUserWidget.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void UPlayerRankingOverviewUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
			if (RankDefinitionTable == nullptr)
			{
				LOG_WARNING(InitializationLog, "RankDefinitionTable not set up in Blueprint!")
				return;
			}

			if (LeagueDefinitionTable == nullptr)
			{
				LOG_WARNING(InitializationLog, "LeagueDefinitionTable not set up in Blueprint!")
				return;
			}

			SizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			SizeBox->SetRenderOpacity(1.f);

			Rank->SetText(FText::FromString(FString::FromInt(GameInstanceAccessor->GetCurrentLevelPoints())));
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);


			static const FString ContextString(TEXT("RankDefinition"));

			TArray<FName> RowNames = RankDefinitionTable->GetRowNames();
			RankDefinitions = TArray<FRankDefinition>();
			for (int32 i = 0; i < RowNames.Num(); i++)
			{
				FRankDefinition* RankDefinition = RankDefinitionTable->FindRow<FRankDefinition >(RowNames[i], ContextString, true);
				RankDefinitions.Add(*RankDefinition);
			}

			QuickSortRankDefinition(RankDefinitions, 0, RankDefinitions.Num() - 1);

			static const FString ContextString2(TEXT("LeagueDefinition"));


			RowNames = LeagueDefinitionTable->GetRowNames();
			LeagueDefinitions = TArray<FLeagueDefinition>();
			for (int32 i = 0; i < RowNames.Num(); i++)
			{
				FLeagueDefinition* RankDefinition = LeagueDefinitionTable->FindRow<FLeagueDefinition >(RowNames[i], ContextString2, true);
				LeagueDefinitions.Add(*RankDefinition);
			}

			int32 CurrentLevelPoints = GameInstanceAccessor->GetCurrentLevelPoints();

			for (int32 i = 0; i < RankDefinitions.Num(); i++)
			{
				if (RankDefinitions[i].LevelPointsToReach > CurrentLevelPoints)
				{
					if (i == 0)
					{
						RankName->SetText(FText::FromString(RankDefinitions[0].RankName));
						League->SetText(FText::FromString(GetLeagueNameForRank(RankDefinitions[0].League)));
						return;
					}
					else
					{
						RankName->SetText(FText::FromString(RankDefinitions[i-1].RankName));
						League->SetText(FText::FromString(GetLeagueNameForRank(RankDefinitions[i - 1].League)));
						return;
					}
				}
				RankName->SetText(FText::FromString(RankDefinitions[RankDefinitions.Num()-1].RankName));
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

void UPlayerRankingOverviewUserWidget::QuickSortRankDefinition(TArray<FRankDefinition>& RankDefinition, int32 Start, int32 End)
{
	if (Start < End)
	{
		int32 Part_Index = PartitionRankDefinition(RankDefinition, Start, End);
		QuickSortRankDefinition(RankDefinition, Start, Part_Index - 1);
		QuickSortRankDefinition(RankDefinition, Part_Index + 1, End);
	}
}

int32 UPlayerRankingOverviewUserWidget::PartitionRankDefinition(TArray<FRankDefinition>& RankDefinition, int32 Start, int32 End)
{
	int32 Pivot = RankDefinition[End].LevelPointsToReach;

	int32 P_Index = Start;

	FRankDefinition temp;

	for (int32 i = Start; i < End; i++)
	{
		if (RankDefinition[i].LevelPointsToReach < Pivot)
		{
			temp = RankDefinition[i];
			RankDefinition[i] = RankDefinition[P_Index];
			RankDefinition[P_Index] = temp;
			P_Index++;
		}
	}

	temp = RankDefinition[End];
	RankDefinition[End] = RankDefinition[P_Index];
	RankDefinition[P_Index] = temp;

	return P_Index;
}

FString UPlayerRankingOverviewUserWidget::GetLeagueNameForRank(ELeagueType LeagueType)
{
	for (auto CurrentLeague : LeagueDefinitions)
	{
		if (CurrentLeague.League == LeagueType)
		{
			return CurrentLeague.LeagueName;
		}
	}
	return "League not found";
}
