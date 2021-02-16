/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "FirstPersonCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;


UCLASS(config = Game)
class THECARETAKER_API AFirstPersonCharacter : public ACharacter, public ICharacterInterface, public IPauseGameInterface
{
	GENERATED_BODY()

protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Components)
	class USceneComponent* DeathSpawnPoint;
	/** Gun mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class AActor* Pickup;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed")
	float RunSpeedModifier;

private:
	IGameInstanceAccessoryInterface* GameInstance;

	UFUNCTION()
	void PlayMonsterSound(USoundBase* MonsterSound);

public:
	void LeftMouseClicked();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace")
	float LineTraceLength;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Run();
	void StopRunning();

	UFUNCTION(BlueprintCallable)
	bool IsRunning() const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Running"))
	void FireRunning(bool IsRunning);

	void Duck();
	void StopDucking();

	bool IsDucking() const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Running"))
	void FireDucking(bool IsRunning);

	//void Crouch();
	//void StopCrouching();

	//bool IsCrouching() const;

	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Running"))
	//void FireCrouching(bool IsRunning);
private:
	bool bIsRunning;
	float WalkSpeedValue;
	float WalkSpeed;
	TSubclassOf<class UNoiseBarUserWidget> NoiseBar;
	bool bIsPaused;
	float TimeDilationValue;
public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void SetSpeedValue(float NewSpeed);

	// Geerbt über ICharacterInterface
	virtual void LeftMouseButton(class ICollectableInterface* &Collectable, bool &bPickupCollected) override;

	// Geerbt über ICharacterInterface
	virtual void RightMouseButton() override;


	// Inherited via IPauseGameInterface
	virtual void SetGamePaused(bool SetGamePaused) override;

	virtual bool IsPaused() const override;

	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void AddControllerYawInput(float Input) override;
	virtual void AddControllerPitchInput(float Input) override;

	// Inherited via ICharacterInterface
	virtual FVector GetDeathSpawnLocation() const override;

	// Inherited via ICharacterInterface
	virtual FRotator GetDeathSpawnRotation() const override;

	// Geerbt über ICharacterInterface
	virtual void SetSpeedMultiplier(float SpeedMultiplier) override;

	// Inherited via ICharacterInterface
	virtual FVector GetLocation() const override;

	// Inherited via ICharacterInterface
	virtual void IsDilatingTime(float Value) override;
};
