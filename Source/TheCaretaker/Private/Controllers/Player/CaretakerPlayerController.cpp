/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Controllers/Player/CaretakerPlayerController.h"

#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameInstance/GameInstanceManager.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Player/CaretakerPlayerState.h"

ACaretakerPlayerController::ACaretakerPlayerController()
{
}

#pragma region Setup InputComponent
void ACaretakerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &ACaretakerPlayerController::LeftMouseButtonClicked);
	InputComponent->BindAction("Released", IE_Pressed, this, &ACaretakerPlayerController::RightMouseButtonClicked);
	InputComponent->BindAction("Escape", IE_Pressed, this, &ACaretakerPlayerController::Escape);
	InputComponent->BindAction("DropLeft", IE_Pressed, this, &ACaretakerPlayerController::DropLeftHand);
	InputComponent->BindAction("DropRight", IE_Pressed, this, &ACaretakerPlayerController::DropRightHand);

	bPickupCollected = false;
}
#pragma endregion

#pragma region BeginPlay
void ACaretakerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bool TestSetup = true;

	Character = Cast<ICharacterInterface>(GetPawn());
	if (Character == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast Character in PlayerController");
		TestSetup = false;
	}
	CaretakerPlayerState = GetPlayerState<ACaretakerPlayerState>();
	if (CaretakerPlayerState == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast PlayerState in PlayerController");
		TestSetup = false;
	}

	if (TestSetup == true)
	{
		LOG_DISPLAY(InitializationLog, "PlayerController setup complete !");
	}
	else
	{
		LOG_WARNING(InitializationLog, "PlayerController setup failed !");
	}
}
#pragma endregion

void ACaretakerPlayerController::SetPickupCollected(bool IsCollected)
{
	bPickupCollected = IsCollected;
}

#pragma region LeftMouseButton Clicked
void ACaretakerPlayerController::LeftMouseButtonClicked()
{	
	if (Character == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Character was null!");
		return;
	}
	ICollectableInterface* Collectable = nullptr;
	Character->LeftMouseButton(Collectable, bPickupCollected);
	if (CaretakerPlayerState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Playstate was null! cannot count collected garbage");
		return;
	}

	if (Collectable != nullptr)
	{
		CaretakerPlayerState->AddCollectableGarbage(Collectable, nullptr);
	}		
}
#pragma endregion

#pragma region Right MouseButton Clicked
void ACaretakerPlayerController::RightMouseButtonClicked()
{
	if (Character == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Character was null!");
		return;
	}
	ICollectableInterface* Collectable = nullptr;
	Collectable = CaretakerPlayerState->RemoveGarbage();
	Character->RightMouseButton();
}
void ACaretakerPlayerController::Escape()
{
	UGameInstanceManager* GameInstance = Cast<UGameInstanceManager>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Cast GameInstance! Is it set in the Projects GameInstance Settings ? This shouldn't happen !");
	}
	else
	{		
		GameInstance->OpenIngameMenu(EIngameMenuCall::IMC_DEFAULT);
	}
}
#pragma endregion

void ACaretakerPlayerController::DropLeftHand()
{
	if (CaretakerPlayerState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Playstate was null! cannot drop collected garbage");
		return;
	}
	CaretakerPlayerState->DropLeft();
}

void ACaretakerPlayerController::DropRightHand()
{
	if (CaretakerPlayerState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Playstate was null! cannot drop collected garbage");
		return;
	}

	CaretakerPlayerState->DropRight();
}
