/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_InstantHunger_PowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_InstantHunger_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Monsters;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMonsterFeedingInterface::StaticClass(), Monsters);

	if (Monsters.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find any Monsters in Scene. This shouldn't happen !")
		return;
	}
	MonsterInterface = Cast<IMonsterFeedingInterface>(Monsters[FMath::RandRange(0, Monsters.Num() - 1)]);
	
}

void ABadLuck_InstantHunger_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (MonsterInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find MonsterInterface. This shouldn't happen !")
	}
	else
	{
		MonsterInterface->InstantMonsterHunger();
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
