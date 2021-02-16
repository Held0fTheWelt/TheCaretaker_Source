/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "InvisibilityPowerUp.h"

#include "Engine/PostProcessVolume.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void AInvisibilityPowerUp::Expired()
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		if (Actor->GetName() == PostProcessingVolumeName)
		{
			APostProcessVolume* Volume = Cast<APostProcessVolume>(Actor);
			if (Volume == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not get Post Processing Volume for PowerUp Effect")
			}
			else
			{
				Volume->bEnabled = false;
			}
		}
	}

	Super::Expired();
}

void AInvisibilityPowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	TArray<AActor*> Actors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		if (Actor->GetName() == PostProcessingVolumeName)
		{
			APostProcessVolume* Volume = Cast<APostProcessVolume>(Actor);
			if (Volume == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not get Post Processing Volume for PowerUp Effect")
			}
			else
			{
				Volume->bEnabled = true;
			}
		}
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
