/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TimeShiftPowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ATimeShiftPowerUp::BeginPlay()
{
	Super::BeginPlay();

	GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ATimeShiftPowerUp::Expired()
{
	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameModeInterface->ClockRunningBackwards(false);
	}

	Super::Expired();
}

void ATimeShiftPowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameModeInterface->ClockRunningBackwards(true);
	}

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
	}
	else
	{
		AchievementInstance->CountAchievement(EAchievementType::AT_PICKUP);
	}
}
