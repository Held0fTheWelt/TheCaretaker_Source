/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "ActorVisibleOnMap.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

AActorVisibleOnMap::AActorVisibleOnMap()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MarkerWidget = nullptr;
	MapMarkerTexture = nullptr;

}

void AActorVisibleOnMap::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterMarkerWidget(true);
}


void AActorVisibleOnMap::RegisterMarkerWidget(bool Register)
{
	if (Register)
	{

		IGameInstanceUIInterface* GameInstance = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameInstance was null !")
				return;
		}

		MarkerWidget = GameInstance->AttachActorMarkerWidget(this, MapMarkerTexture, false);
		LOG_DISPLAY(InitializationLog, "Marker Widget for Actor on Map setup okay!");
	}
	else
	{
		TArray<UUserWidget*> Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UMiniMapInterface::StaticClass(), false);
		if (Widgets.Num() == 0)
		{
			LOG_WARNING(RuntimeExecutionLog, "Widget Array was length 0. No MiniMap found. This shouldn't happen !")
		}
		else
		{
			for (auto Widget : Widgets)
			{
				IMiniMapInterface* MiniMap = Cast<IMiniMapInterface>(Widget);
				if (MiniMap == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "Could not cast Actor to MiniMap. This shouldn't happen !")
				}
				else
				{
					MiniMap->UnregisterWidgetInterface(MarkerWidget);
					MarkerWidget->UnregisterActorMarkerWidget();
					MarkerWidget->RemoveFromParent();
				}
			}
		}
	}
}
