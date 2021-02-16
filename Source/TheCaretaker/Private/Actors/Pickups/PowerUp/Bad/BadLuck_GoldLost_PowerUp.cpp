/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_GoldLost_PowerUp.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_GoldLost_PowerUp::Expired()
{
	Super::Expired();
}

void ABadLuck_GoldLost_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameModeInterface->DropGold();
	}

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
	}
	else
	{
		AchievementInstance->CountAchievement(EAchievementType::AT_BAD_PICKUP);
	}
}
