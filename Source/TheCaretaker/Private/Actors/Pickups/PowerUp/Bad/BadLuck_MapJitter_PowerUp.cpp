/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_MapJitter_PowerUp.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

void ABadLuck_MapJitter_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UActorMarkerWidgetInterface::StaticClass(), false);

	if (Widgets.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find any MiniMap Interface Widgets")
	}
	else
	{
		for (auto Widget : Widgets)
		{
			MiniMapInterfaces.Add(Cast<IActorMarkerWidgetInterface>(Widget));
		}
	}
}

void ABadLuck_MapJitter_PowerUp::Expired()
{
	if (MiniMapInterfaces.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find any MiniMap Interface Widgets")
	}
	else
	{
		for (int32 i = 0; i < MiniMapInterfaces.Num(); i++)
		{
			MiniMapInterfaces[i]->AddJitterToMapWidget(false);
		}
	}

	Super::Expired();
}

void ABadLuck_MapJitter_PowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);


	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UActorMarkerWidgetInterface::StaticClass(), false);

	if (Widgets.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find any MiniMap Interface Widgets")
	}
	else
	{
		for (auto Widget : Widgets)
		{
			MiniMapInterfaces.Add(Cast<IActorMarkerWidgetInterface>(Widget));
		}
	}

	if (MiniMapInterfaces.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "Could not find any MiniMap Interface Widgets")
	}
	else
	{
		for (int32 i = 0; i < MiniMapInterfaces.Num(); i++)
		{
			MiniMapInterfaces[i]->AddJitterToMapWidget(true);
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
