/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Garbage/GarbageActor.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Player/CaretakerPlayerState.h"
#include "States/Game/CaretakerGameState.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

AGarbageActor::AGarbageActor()
{
	bSupressDoubleClick = false;

}
#pragma region Begin Play
void AGarbageActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>GameStateActors;
	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerGameState::StaticClass(), GameStateActors);
	for (const auto& Actor : GameStateActors) {

		ACaretakerGameState* GameStateActor = Cast<ACaretakerGameState>(Actor);
		if (GameStateActor != nullptr)
		{
			GarbageCollected.AddDynamic(GameStateActor, &ACaretakerGameState::GarbageCollected);
		}
	}

	RegisterMarkerWidget(true);

}
#pragma endregion
void AGarbageActor::RegisterMarkerWidget(bool Register)
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
		LOG_DISPLAY(InitializationLog, "Marker Widget setup okay!");
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

void AGarbageActor::SetMarkerWidget(UActorMarkerWidget* NewMarkerWidget)
{
	MarkerWidget = NewMarkerWidget;
}

int32 AGarbageActor::GetSpawnInformationIndex() const
{
	return SpawnInformationIndex;
}

#pragma region Left MouseButton Clicked
void AGarbageActor::LeftMouseClicked()
{
	if (bSupressDoubleClick == true)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Prevent DoubleClick Duplicate Behaviour")
		return;
	}

	APlayerController* Player = UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0);
	if (Player == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot count collect garbage, because could not find player controller! This shouldn't happen!");
		return;
	}

	ACaretakerPlayerState* PlayerState = Player->GetPlayerState<ACaretakerPlayerState>();
	if (PlayerState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot count collect garbage, because could not find player state in controller! This shouldn't happen!");
		return;
	}

	if (PlayerState->GetCurrentLimitStatus() == false)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Inventory Limit exceeded. Will not carry garbage");
		return;
	}

	bSupressDoubleClick = true;

	Super::LeftMouseClicked();	

	if (GarbageCollected.IsBound())
	{
		GarbageCollected.Broadcast(Part);
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot count Garbage collect, because it is unbound !!");
	}

	RegisterMarkerWidget(false);
}
#pragma endregion