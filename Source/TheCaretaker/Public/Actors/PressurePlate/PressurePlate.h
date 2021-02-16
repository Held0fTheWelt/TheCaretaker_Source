/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class THECARETAKER_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	// TimerHandle to do timing
	FTimerHandle TimerHandle;

	// Delay to call Close
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	float Delay;
	   
	// Switches Open / Close
	bool bSwitchIsOn;
	// Method called, when TimerHandle is finished. Calls Closing Behaviour
	void TimerHandleFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
		
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UPROPERTY(EditAnywhere)
	//TArray<class AMovingPlatform*> PlatformsToTrigger;
};
