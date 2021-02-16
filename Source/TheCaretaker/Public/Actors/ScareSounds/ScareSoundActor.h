/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScareSoundActor.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FScareSoundList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class USoundWave*> ScareSounds;

public:
	FScareSoundList()
	{

	}
};

UCLASS()
class THECARETAKER_API AScareSoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AScareSoundActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScareSounds")
	FScareSoundList ScareSounds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MinSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MaxSeconds;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UAudioComponent* ScareSoundComponent;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	/* Handle to manage the timer */
	FTimerHandle ScareSoundTimerHandle;

	UFUNCTION()
	void OnScareSoundEvent();
};
