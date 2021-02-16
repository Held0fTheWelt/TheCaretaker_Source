/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "ClockFreezePowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void AClockFreezePowerUp::BeginPlay()
{
	Super::BeginPlay();

	GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));	
}

void AClockFreezePowerUp::Expired()
{
	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameModeInterface->SetClockActive(true);
	}

	Super::Expired();
}

void AClockFreezePowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find GameMode Interface. This shouldn't happen !")
	}
	else
	{
		GameModeInterface->SetClockActive(false);
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
