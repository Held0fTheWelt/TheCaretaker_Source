/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "ActorVisibleOnMap.generated.h"

UCLASS()
class THECARETAKER_API AActorVisibleOnMap : public ATargetPoint
{
	GENERATED_BODY()
	
public:	
	AActorVisibleOnMap();

protected:	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class UTexture2D* MapMarkerTexture;

	UPROPERTY()
	class UActorMarkerWidget* MarkerWidget;

	void RegisterMarkerWidget(bool Register);
};
