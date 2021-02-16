/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_MapReadError_PowerUp.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_MapReadError_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ABadLuck_MapReadError_PowerUp::Expired()
{
	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameInstance->SetMapActive(true);
	}

	Super::Expired();
}

void ABadLuck_MapReadError_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameInstance->SetMapActive(false);
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
