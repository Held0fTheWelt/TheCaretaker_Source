/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Map/MiniMapWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Interfaces/ActorMarker/ActorMarkerWidgetInterface.h"
#include "Log/GlobalLog.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

void UMiniMapWidget::AddActorMarker(UActorMarkerWidget* MonsterMarker)
{
	Markers.Add(MonsterMarker);
	
	MarkerPanel->AddChild(MonsterMarker);
	
	MonsterMarker->InitializePosition();
}

void UMiniMapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/*for (auto Marker : MonsterMarkers)
	{
		Marker->GetCurrentPosition();
	}*/

}

void UMiniMapWidget::UnregisterWidgetInterface(IActorMarkerWidgetInterface* Marker)
{
	if (Markers.Contains(Marker))
	{
		Markers.Remove(Marker);
		LOG_DISPLAY(RuntimeExecutionLog, "Marker Widget removed from list.")
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Marker Widget could not be removed from list, because it was not known. This shouldn't happen !")
	}
}

float UMiniMapWidget::GetVectorLength()
{
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (CanvasSlot == nullptr)
	{
		LOG_WARNING(InitializationLog, "CanvasPanel was null !")
		return 0.0f;
	}
	FVector2D Size = CanvasSlot->GetSize();

	return (Size.X / 2) * (Size.Y / 2);
}

