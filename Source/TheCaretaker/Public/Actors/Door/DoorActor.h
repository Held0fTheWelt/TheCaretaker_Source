/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Secrets/SecretLockActor.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/Door/DoorInterface.h"
#include "Components/TimelineComponent.h"
#include "DoorActor.generated.h"





UCLASS()
class THECARETAKER_API ADoorActor : public ASecretLockActor, public IMouseInteractionInterface, public IDoorInterface
{
	GENERATED_BODY()
	
public:	
	ADoorActor();

protected:
#pragma region Components
	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume1;
	
	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume2;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class USceneComponent* Pivot;
#pragma endregion
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	float MaxTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	TEnumAsByte<EPartInformation> DoorLevel;

	bool bDoorCanOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	float DoorOpeningTriggerVolume1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	float DoorOpeningTriggerVolume2;

#pragma region Timer Component
	// Delay to call Close
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	float Delay;

	// TimerHandle to do timing
	FTimerHandle DoorDelayTimerHandle;

	// Switches Open / Close
	bool bDoorIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	bool bDoorIsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	bool bDoorIsUsable;
	
	// Method called, when TimerHandle is finished. Calls Closing Behaviour
	void TimerHandleFinished();
#pragma endregion

#pragma region Blueprint Events
	UFUNCTION(Category = "Door Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Opening();

	UFUNCTION(Category = "Door Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Closing();

	UFUNCTION(Category = "Door Actions", BlueprintImplementableEvent, BlueprintCallable)
	void Closed();
#pragma endregion

#pragma region TimeLine	
	UPROPERTY()
	class UTimelineComponent* AnimationTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door Settings")
	class UCurveFloat* FloatCurve;


	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	void PlayTimeline();

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
#pragma endregion

protected:
	virtual void BeginPlay() override;

	float InitialRotation;
public:	
	virtual void Tick(float DeltaTime) override;

#pragma region Collision Volume
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion

private:
	// Function to open the door
	void OpenDoor();

	void InitTimeLine();

	// Geerbt über IMouseInteractionInterface
	virtual void LeftMouseButtonClicked(class ICollectableInterface* &CollectableRef);

	float CurrentDirection;
	
	// Inherited via IDoorInterface
	virtual void SetDoorEnabled(bool CanBeUsed);

	// Inherited via IDoorInterface
	virtual TEnumAsByte<EPartInformation> GetDoorLevel() const override;

	// Geerbt über IDoorInterface
	virtual void OpenDoorByMaster() override;
};
