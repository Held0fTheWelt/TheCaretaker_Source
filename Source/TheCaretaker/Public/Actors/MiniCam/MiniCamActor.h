/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "Interfaces/MiniMapActor/MiniMapActorInterface.h"
#include "MiniCamActor.generated.h"

UCLASS()
class THECARETAKER_API AMiniCamActor : public ASceneCapture2D, public IMiniMapActorInterface
{
	GENERATED_BODY()
	
public:	
	AMiniCamActor();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual float RegisterActorMarker(class IActorMarkerWidgetInterface* Marker, bool Register) override;
	
private:
	class APawn* PlayerPawn;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float AmountOfZoomChange;
	UPROPERTY(VisibleAnywhere, Category = "Zoom")
	float CurrentZoom;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomMin;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomMax;

	class APlayerController* PlayerController;

private:
	void ZoomMapCamera(float Value);

	TArray<class IActorMarkerWidgetInterface*> ActorMarkers;

	bool bIsTutorialMode;

	bool bMapFailure;

	// Inherited via IMiniMapActorInterface
	virtual void SetMapFailure(bool HasFailure) override;
};
