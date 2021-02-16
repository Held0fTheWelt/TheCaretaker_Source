/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ActorMarker/MarkerWidgetActorInterface.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/Traps/TrapInterface.h"
#include "Components/TimelineComponent.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "TrapActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTrapIsSolved);

UCLASS()
class THECARETAKER_API ATrapActor : public AActor, public IMouseInteractionInterface, public ITrapInterface, public IMarkerWidgetActorInterface
{
	GENERATED_BODY()
	
public:	
	ATrapActor();

protected:
#pragma region Components
	/** TriggerVolume to activate and deactivate ChestBehaviour */
	UPROPERTY(VisibleAnywhere, Category = Components)
	class UBoxComponent* TriggerVolume;

	/** Mesh to show the Chest */
	UPROPERTY(VisibleAnywhere, Category = Components)
	class UStaticMeshComponent* BaseMesh;

	/** Mesh to show the Chests Cover */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Components)
	class UStaticMeshComponent* TrapMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Components)
	class UAudioComponent* AudioComponent;

#pragma endregion
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	float HeightWhenArmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	bool bIsArmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class UTexture2D* MapMarkerTexture;

public:
	virtual void LeftMouseButtonClicked(class ICollectableInterface*& CollectableRef);

	virtual void TrapSolved();

	FTrapIsSolved TrapIsSolved;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Part")
	TEnumAsByte<EPartInformation> Part;

#pragma region Blueprint Events
	UFUNCTION(Category = "Trap Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Interacted();

	UFUNCTION(Category = "Trap Actions", BlueprintImplementableEvent, BlueprintCallable)
	void ArmingTrap();
	
	UFUNCTION(Category = "Trap Actions", BlueprintImplementableEvent, BlueprintCallable)
	void TrapSnapping();

	UFUNCTION(Category = "Trap Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Armed();
#pragma endregion

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	class UFMODAudioComponent* FMODAudio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise Sound")
	FName FMODParameterName;

#pragma region Timer Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	class USoundBase* InteractingSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	class USoundBase* BeginInteractSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	class USoundBase* TrapSnapSound;

private:
	// TimerHandle to do timing
	FTimerHandle ChestTimerHandle;

	// Method called, when TimerHandle is finished. Calls Closing Behaviour
	void TimerHandleFinished();
#pragma endregion
	void ArmTrap();

	bool bCanArmTrap;

	bool bBlockInteraction;

	class ACaretakerPlayerState* CurrentPlayerState;

	IGameInstanceUIInterface* UIInstance;
protected:
#pragma region TimeLine	
	UPROPERTY()
	class UTimelineComponent* AnimationTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	class UCurveFloat* TrapAimCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Settings")
	class UCurveFloat* TrapSnapCurve;

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

	void PlaySnapSound();

	void InitTimeline(class UCurveFloat* CurrentCurve);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	float CurrentHeight;

	class APlayerController* PlayerController;

	void RegisterMarkerWidget(bool Register);

	UPROPERTY()
	class UActorMarkerWidget* MarkerWidget;

	// Inherited via IMarkerWidgetActorInterface
	virtual void SetMarkerWidget(UActorMarkerWidget* MarkerWidget);
};
