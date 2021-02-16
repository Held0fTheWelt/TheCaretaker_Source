/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "FinishedTimedGameMode.h"

#include "Engine/GameInstance.h"
#include "GameInstance/GameInstanceManager.h"

void AFinishedTimedGameMode::Finish()
{
	UGameInstance* GameInstance = GetGameInstance();

	UGameInstanceManager* GameInstanceManager = Cast<UGameInstanceManager>(GameInstance);

	if (GameInstanceManager != nullptr)
	{
		if (bPlaySecrets)
		{

		}
		else
		{
			GameInstanceManager->SetCurrentLevelName(MapToLoad);
			GameInstanceManager->LoadLevelFinished();
		}
	}
}