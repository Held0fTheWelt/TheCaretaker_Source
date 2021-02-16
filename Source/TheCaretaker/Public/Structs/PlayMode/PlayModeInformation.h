/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Engine/DataTable.h"
#include "Structs/Level/LevelSetup.h"
#include "PlayModeInformation.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPlayModeInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPlayModeInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayMode")
	EPlayMode PlayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TArray<FLevelSetup> Levels;

	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override;
};

