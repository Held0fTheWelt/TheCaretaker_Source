/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_Noisy_PowerUp.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ABadLuck_Noisy_PowerUp::ABadLuck_Noisy_PowerUp()
{
	NoiseModifier = 5.f;
}

void ABadLuck_Noisy_PowerUp::BeginPlay()
{
	Super::BeginPlay();	
}

void ABadLuck_Noisy_PowerUp::Expired()
{
	if (NoiseBarInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find NoiseBar Widget Interface. This shouldn't happen !")
	}
	else
	{
		NoiseBarInterface->NoisyPickup();
	}

	if (Monsters.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Monsters found.")
	}
	else
	{
		for (auto Monster : Monsters)
		{
			Monster->NoisyPickup(false);
		}
	}

	Super::Expired();
}

void ABadLuck_Noisy_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	TArray<UUserWidget*> Widgets;

	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UNoiseBarWidgetInterface::StaticClass(), false);

	if (Widgets.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find any NoiseBar Widget Interface. This shouldn't happen !")
	}
	else
	{
		NoiseBarInterface = Cast<INoiseBarWidgetInterface>(Widgets[0]);
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMonsterFeedingInterface::StaticClass(), Actors);

	if (Actors.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Monsters found !")
	}
	else
	{
		for (auto Actor : Actors)
		{
			IMonsterFeedingInterface* Volume = Cast<IMonsterFeedingInterface>(Actor);
			if (Volume == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not cast Actor to Interface. This shouldn't happen !")
			}
			else
			{
				Monsters.Add(Volume);
			}
		}
	}

	if (NoiseBarInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find NoiseBar Widget Interface. This shouldn't happen !")
	}
	else
	{
		NoiseBarInterface->NoisyPickup(NoiseModifier);
	}

	if (Monsters.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Monsters found.")
	}
	else
	{
		for (auto Monster : Monsters)
		{
			Monster->NoisyPickup(true);
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