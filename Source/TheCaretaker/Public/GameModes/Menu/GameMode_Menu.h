/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameMode/Menu/MenuGameModeInterface.h"
#include "GameMode_Menu.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AGameMode_Menu : public AGameModeBase, public IMenuGameModeInterface
{
	GENERATED_BODY()
	
public:
	AGameMode_Menu();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Quit")
	void PlayQuitSequence();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAchievementInputVisible;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Components)
	class UMenuAudioComponent* MenuAudioComponent;

private:
	bool SetupUI();

	void SetupContinueButton();
private:
	bool GetInstanceInterfaces();

	class IGameInstanceInterface* GameInstance;
	class IGameInstanceAccessoryInterface* GameInstanceAccessory;
	class IGameInstanceUIInterface* GameInstanceUI;
};
