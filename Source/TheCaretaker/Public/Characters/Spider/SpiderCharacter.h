/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Interfaces/Characters/Spider/SpiderInterface.h"
#include "SpiderCharacter.generated.h"

UCLASS()
class THECARETAKER_API ASpiderCharacter : public ACharacter, public IPauseGameInterface, public ISpiderInterface
{
	GENERATED_BODY()

public:
	ASpiderCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetGamePaused(bool SetGamePaused) override;

	virtual bool IsPaused() const;

	void SetPatrolPoints(TArray<class AConnectedTargetPoint*> PatrolPoints);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* NotificationTrigger;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class USoundBase* SpiderAttackSound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class UAnimationAsset* FightAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class UTexture2D* MapMarkerTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Patrol")
	TArray<AConnectedTargetPoint*> PatrolPoints;

private:
	bool bPaused;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void NotifyOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Power Ups")
	FString PostProcessingVolumeName;	

	UPROPERTY()
	class UActorMarkerWidget* MarkerWidget;

	void RegisterMarkerWidget(bool Register);

	// Geerbt über ISpiderInterface
	virtual float SetAnimRate(float AnimRate) override;
	virtual float SetMoveSpeed(float MoveSpeed);
};
