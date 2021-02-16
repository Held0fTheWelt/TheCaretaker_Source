/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Structs/Heat/HeatDefinition.h"
#include "Structs/Heat/PlayerTypeDefinition.h"
#include "PlayerHeatUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UPlayerHeatUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerHeatUserWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerHeat;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerType;

protected:
	UPROPERTY(EditAnywhere)
	class UDataTable* HeatDefinitionTable;
	
	UPROPERTY(EditAnywhere)
	class UDataTable* PlayerTypeDefinitionTable;

	UPROPERTY(VisibleAnywhere)
	TArray<FHeatDefinition> HeatDefinitions;

	UPROPERTY(VisibleAnywhere)
	TArray<FPlayerTypeDefinition> PlayerTypeDefinitions;

private:
	IGameInstanceAccessoryInterface* GameInstanceAccessor;

private:
	void ReadInDataTables();
	void QuickSortHeatDefinition(TArray<FHeatDefinition>& RankDefinition, int32 Start, int32 End);
	int32 PartitionHeatDefinition(TArray<FHeatDefinition>& RankDefinition, int32 Start, int32 End);
};
