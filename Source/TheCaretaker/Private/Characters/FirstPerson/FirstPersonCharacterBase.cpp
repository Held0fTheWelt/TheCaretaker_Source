/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Characters/FirstPerson/FirstPersonCharacter.h"

#include "Animation/AnimInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Widgets/NoiseBar/NoiseBarUserWidget.h"
//////////////////////////////////////////////////////////////////////////
// Input

#pragma region Setup Player InputComponent
void AFirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Set up gameplay key bindings

	// Bind run events
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AFirstPersonCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFirstPersonCharacter::StopRunning);
	
	// Bind duck events
	PlayerInputComponent->BindAction("Duck", IE_Pressed, this, &AFirstPersonCharacter::Duck);
	PlayerInputComponent->BindAction("Duck", IE_Released, this, &AFirstPersonCharacter::StopDucking);
	
	// Bind crouch events
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFirstPersonCharacter::Crouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFirstPersonCharacter::StopCrouching);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFirstPersonCharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AFirstPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFirstPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFirstPersonCharacter::LookUpAtRate);		
}
#pragma endregion

#pragma region Run
void AFirstPersonCharacter::Run()
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - no game influence on Run");
		return;
	}

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkSpeed * RunSpeedModifier;
	bIsRunning = true;
	FireRunning(bIsRunning);
	
	TArray<UUserWidget*> Widgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, *NoiseBar, false);

	for (auto widget : Widgets)
	{
		UNoiseBarUserWidget* CurrentNoiseBar = Cast<UNoiseBarUserWidget>(widget);

		if (CurrentNoiseBar != nullptr)
		{
			CurrentNoiseBar->CharacterRunning(true);
		}
		else
		{
			LOG_WARNING(RuntimeLog, "Could not find NoiseBar on Running. This shouldn't happen!");
		}
	}
}
#pragma endregion

#pragma region Stop Running
void AFirstPersonCharacter::StopRunning()
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - no game influence of Stop Running");
		return;
	}

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkSpeed;
	bIsRunning = false;
	FireRunning(bIsRunning);
	
	TArray<UUserWidget*> Widgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, *NoiseBar, false);

	for (auto widget : Widgets)
	{
		UNoiseBarUserWidget* CurrentNoiseBar = Cast<UNoiseBarUserWidget>(widget);

		if (CurrentNoiseBar != nullptr)
		{
			CurrentNoiseBar->CharacterRunning(false);
		}
		else
		{
			LOG_WARNING(RuntimeLog, "Could not find NoiseBar on Running. This shouldn't happen!");
		}
	}
}
#pragma endregion

#pragma region Is Running
bool AFirstPersonCharacter::IsRunning() const
{
	return bIsRunning;
}
#pragma endregion

void AFirstPersonCharacter::Duck()
{
}

void AFirstPersonCharacter::StopDucking()
{
}

bool AFirstPersonCharacter::IsDucking() const
{
	return false;
}

//void AFirstPersonCharacter::Crouch()
//{
//}
//
//void AFirstPersonCharacter::StopCrouching()
//{
//}
//
//bool AFirstPersonCharacter::IsCrouching() const
//{
//	return false;
//}


void AFirstPersonCharacter::MoveForward(float Value)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not moving forward");
		return;
	}
	if (Value != 0.0f)
	{
		// Add movement in that direction		
		AddMovementInput(GetActorForwardVector(), Value * TimeDilationValue);
	}
}

void AFirstPersonCharacter::MoveRight(float Value)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not moving right");
		return;
	}
	if (Value != 0.0f)
	{
		// Add movement in that direction		
		AddMovementInput(GetActorRightVector(), Value * TimeDilationValue);
	}
}

void AFirstPersonCharacter::TurnAtRate(float Rate)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not turning");
		return;
	}
	// Calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * TimeDilationValue * GetWorld()->GetDeltaSeconds());
}

void AFirstPersonCharacter::LookUpAtRate(float Rate)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not looking up");
		return;
	}
	// Calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * TimeDilationValue * GetWorld()->GetDeltaSeconds());
}