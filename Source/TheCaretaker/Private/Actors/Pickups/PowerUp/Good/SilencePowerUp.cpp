/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SilencePowerUp.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ASilencePowerUp::BeginPlay()
{
	Super::BeginPlay();
}

void ASilencePowerUp::Expired()
{
	if (NoiseBarInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find NoiseBar Widget Interface. This shouldn't happen !")
	}
	else
	{
		NoiseBarInterface->NoisePickupBlockingNoise(false);
	}

	Super::Expired();
}

void ASilencePowerUp::Activated(AActor* OtherActor)
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

	if (NoiseBarInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find NoiseBar Widget Interface. This shouldn't happen !")
	}
	else
	{
		NoiseBarInterface->NoisePickupBlockingNoise(true);
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
