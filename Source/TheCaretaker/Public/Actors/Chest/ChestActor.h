/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/ActorMarker/MarkerWidgetActorInterface.h"
#include "Interfaces/Chests/ChestInterface.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Components/TimelineComponent.h"
#include "ChestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChestIsSolved, TEnumAsByte<EPartInformation>, Part);

UENUM(BlueprintType)
enum class ERotationAxis : uint8
{
	RA_NONE		UMETA(DisplayName = "None"),
	RA_X		UMETA(DisplayName = "Axis X"),
	RA_Y		UMETA(DisplayName = "Axis Y"),
	RA_Z		UMETA(DisplayName = "Axis Z")
};

/** ChestActor is used to set up a chest, that has to be refilled with Gold */
UCLASS()
class THECARETAKER_API AChestActor : public AActor, public IMouseInteractionInterface, public IChestInterface, public IMarkerWidgetActorInterface
{
	GENERATED_BODY()
	
public:	
	AChestActor();

protected:
#pragma region Components
	/** TriggerVolume to activate and deactivate ChestBehaviour */
	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume;

	/** Mesh to show the Chest */
	UPROPERTY(VisibleAnywhere, Category = Components)
	class UStaticMeshComponent* ChestMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USceneComponent* ChestRoot;
	/** Mesh to show the Chests Cover */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Mesh")
	class UStaticMeshComponent* CoverMesh;

	/** Mesh to show the Gold Cover */
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* GoldCoverMesh;
#pragma endregion
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Settings")
	float AngleWhenOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class UTexture2D* MapMarkerTexture;

	UPROPERTY()
	class UActorMarkerWidget* MarkerWidget;

	bool bIsClosed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Chest Settings")
	ERotationAxis RotationAxis;
	void RegisterMarkerWidget(bool Register);

public:	
	virtual void LeftMouseButtonClicked(class ICollectableInterface* &CollectableRef);
	
	FChestIsSolved ChestIsSolved;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Part")
	TEnumAsByte<EPartInformation> Part;

#pragma region Blueprint Events
	UFUNCTION(Category = "Chest Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Interacted();

	UFUNCTION(Category = "Chest Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Closing();

	UFUNCTION(Category = "Chest Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Closed();
#pragma endregion

#pragma region Timer Component
	// Delay to call Close
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Settings")
	float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Settings")
	class USoundBase* InteractingSound;

private:
	// TimerHandle to do timing
	FTimerHandle ChestTimerHandle;

	// Method called, when TimerHandle is finished. Calls Closing Behaviour
	void TimerHandleFinished();
#pragma endregion
	void CloseChest();

	bool bCanCloseChest;

	bool bBlockInteraction;

	class ACaretakerPlayerState* CurrentPlayerState;
protected:
#pragma region TimeLine	
	UPROPERTY()
	class UTimelineComponent* AnimationTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Settings")
	class UCurveFloat* FloatCurve;

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	void PlayTimeline();

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
#pragma endregion

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float CurrentAngle;

	// Inherited via IMarkerWidgetActorInterface
	virtual void SetMarkerWidget(UActorMarkerWidget* MarkerWidget);
};
