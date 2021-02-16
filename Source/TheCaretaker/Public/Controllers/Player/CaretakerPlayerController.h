/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "GameFramework/PlayerController.h"
#include "CaretakerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ACaretakerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACaretakerPlayerController();

	void SetPickupCollected(bool IsCollected);

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void LeftMouseButtonClicked();
	UFUNCTION()
	void RightMouseButtonClicked();
	UFUNCTION()
	void Escape();
	UFUNCTION()
	void DropLeftHand();
	UFUNCTION()
	void DropRightHand();
	
private:
	class ICharacterInterface* Character;
	class ACaretakerPlayerState* CaretakerPlayerState;

protected:
	UPROPERTY(VisibleAnywhere)
	bool bPickupCollected;
};
