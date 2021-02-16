/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_OneHanded_PowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_OneHanded_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	PlayerStateInterface = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<IPlayerStateInterface>();

	if (PlayerStateInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayerStateInterface. This shouldn't happen!")
	}
}

void ABadLuck_OneHanded_PowerUp::Expired()
{
	if (PlayerStateInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayerStateInterface. This shouldn't happen!")
	}
	else
	{
		PlayerStateInterface->AddItemSlot();
	}
	
	Super::Expired();
}

void ABadLuck_OneHanded_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (PlayerStateInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayerStateInterface. This shouldn't happen!")
	}
	else
	{
		PlayerStateInterface->RemoveItemSlot(false);

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
