/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_NoUI_PowerUp.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Log/GlobalLog.h"

void ABadLuck_NoUI_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ABadLuck_NoUI_PowerUp::Expired()
{
	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameInstance->SetUIActive(true);
	}

	Super::Expired();
}

void ABadLuck_NoUI_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameInstance->SetUIActive(false);
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
