/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_Death_PowerUp.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_Death_PowerUp::Expired()
{
	Super::Expired();
}

void ABadLuck_Death_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
	}
	else
	{
		Menu->OpenIngameMenu(EIngameMenuCall::IMC_DEATHBYPICKUP);
	}

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")		
	}
	else
	{
		AchievementInstance->CountAchievement(EAchievementType::AT_DEATHBYPICKUP);
	}
}
