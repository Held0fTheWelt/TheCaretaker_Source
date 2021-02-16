/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Structs/Rank/RankDefinition.h"
#include "Structs/Rank/LeagueDefinition.h"
#include "PlayerRankingOverviewUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UPlayerRankingOverviewUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* League;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* RankName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Rank;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	class UDataTable* LeagueDefinitionTable;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* RankDefinitionTable;

private:
	IGameInstanceAccessoryInterface* GameInstanceAccessor;

	TArray<FRankDefinition> RankDefinitions;
	TArray<FLeagueDefinition> LeagueDefinitions;

private:
	void QuickSortRankDefinition(TArray<FRankDefinition> &RankDefinition, int32 Start, int32 End);
	int32 PartitionRankDefinition(TArray<FRankDefinition>& RankDefinition, int32 Start, int32 End);
	FString GetLeagueNameForRank(ELeagueType LeagueType);
};
