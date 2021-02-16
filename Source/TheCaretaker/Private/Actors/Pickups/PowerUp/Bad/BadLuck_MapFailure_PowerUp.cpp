/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_MapFailure_PowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_MapFailure_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMiniMapActorInterface::StaticClass(), Actors);

	if (Actors.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find MiniMapInterface ! This shouldn't happen !")
	}
	else
	{
		MiniMapInterface = Cast<IMiniMapActorInterface>(Actors[0]);
	}
}

void ABadLuck_MapFailure_PowerUp::Expired()
{
	if (MiniMapInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find MiniMapInterface ! This shouldn't happen !")
	}
	else
	{
		MiniMapInterface->SetMapFailure(false);
	}
	
	Super::Expired();
}

void ABadLuck_MapFailure_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (MiniMapInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find MiniMapInterface ! This shouldn't happen !")
	}
	else
	{
		MiniMapInterface->SetMapFailure(true);
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
