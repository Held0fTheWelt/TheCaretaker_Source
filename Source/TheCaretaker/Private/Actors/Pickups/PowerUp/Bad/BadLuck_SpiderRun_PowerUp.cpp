/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_SpiderRun_PowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Log/GlobalLog.h"

void ABadLuck_SpiderRun_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors = TArray<AActor*>();
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USpiderInterface::StaticClass(), Actors);

	if (Actors.Num() == 0)
	{
		LOG_WARNING(InitializationLog,"No Actors with SpiderInterface found")
		return;
	}

	for (auto Actor : Actors)
	{
		ISpiderInterface* SpiderInterface = Cast<ISpiderInterface>(Actor);
		if (SpiderInterface == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast Actor to SpiderInterface")
		}
		else
		{
			SpidersInScene.Add(SpiderInterface);
		}
	}
}

void ABadLuck_SpiderRun_PowerUp::Expired()
{
	if (SpidersInScene.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Spiders found in Scene")
	}
	else
	{
		for (auto SpiderInterface : SpidersInScene)
		{
			SpiderInterface->SetAnimRate(PreviousAnimRate);
			SpiderInterface->SetMoveSpeed(PreviousWalkSpeed);
		}
	}

	Super::Expired();
}

void ABadLuck_SpiderRun_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (SpidersInScene.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Spiders found in Scene")
	}
	else
	{
		for (auto SpiderInterface : SpidersInScene)
		{
			PreviousAnimRate = SpiderInterface->SetAnimRate(AnimRate);
			PreviousWalkSpeed = SpiderInterface->SetMoveSpeed(MaxWalkSpeed);
		}
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
