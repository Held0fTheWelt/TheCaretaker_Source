/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Click/ClickActor.h"
#include "Interfaces/Garbage/GarbageInterface.h"
#include "Interfaces/ActorMarker/MarkerWidgetActorInterface.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "GarbageActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGarbageCollected, TEnumAsByte<EPartInformation>, Part);
/**
 * 
 */
UCLASS()
class THECARETAKER_API AGarbageActor : public AClickActor, public IGarbageInterface, public IMarkerWidgetActorInterface
{
	GENERATED_BODY()
	
public:
	AGarbageActor();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Part")
	TEnumAsByte<EPartInformation> Part;

public:
	virtual void LeftMouseClicked() override;

protected:
	virtual void BeginPlay() override;

	void RegisterMarkerWidget(bool Register);

private:
	FGarbageCollected GarbageCollected;	

	bool bSupressDoubleClick;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class UTexture2D* MapMarkerTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnInformation")
	int32 SpawnInformationIndex;

	UPROPERTY()
	class UActorMarkerWidget* MarkerWidget;

	// Inherited via IMarkerWidgetActorInterface
	virtual void SetMarkerWidget(UActorMarkerWidget* MarkerWidget);

	// Inherited via IGarbageInterface
	virtual int32 GetSpawnInformationIndex() const;
};
