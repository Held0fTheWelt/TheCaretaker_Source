/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "InventoryPowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void AInventoryPowerUp::BeginPlay()
{
	Super::BeginPlay();

	PlayerStateInterface = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<IPlayerStateInterface>();

	if (PlayerStateInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayerStateInterface. This shouldn't happen!")
	}
}

void AInventoryPowerUp::Expired()
{
	Super::Expired();
}

void AInventoryPowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (PlayerStateInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find PlayerStateInterface. This shouldn't happen!")
	}
	else
	{
		PlayerStateInterface->AddItemSlot();
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
