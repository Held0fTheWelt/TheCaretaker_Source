/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/PlayMode/PlayModeInformation.h"
#include "Enums/PlayMode/PlayMode.h"


FPlayModeInformation::FPlayModeInformation()
{
	PlayMode = EPlayMode::PM_NONE;
	Levels = TArray<FLevelSetup>();
}

void FPlayModeInformation::OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems)
{
	Super::OnPostDataImport(InDataTable, InRowName, OutCollectedImportProblems);

	if (PlayMode == EPlayMode::PM_CLASSIC)
	{
		for (auto Level : Levels)
		{

		}
	}
}
