/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "MiniMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMiniMapWidget : public UUserWidget , public IMiniMapInterface
{
	GENERATED_BODY()
	
public:
	
	void AddActorMarker(class UActorMarkerWidget* MonterMarker);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MarkerPanel;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void UnregisterWidgetInterface(class IActorMarkerWidgetInterface* Marker) override;
private:
	TArray<class IActorMarkerWidgetInterface*> Markers;

	virtual float GetVectorLength();

};
