/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "ClickActor.generated.h"

UCLASS()
class THECARETAKER_API AClickActor : public AActor, public IMouseInteractionInterface, public ICollectableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClickActor();

	virtual void LeftMouseClicked();
protected:
	virtual void BeginPlay() override;

	UFUNCTION(Category = "Collected Pickpup", BlueprintImplementableEvent, BlueprintCallable)
	void Collected();

	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

private:

	// Geerbt über IMouseInteractionInterface
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef);
	virtual AActor* GetActor() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
