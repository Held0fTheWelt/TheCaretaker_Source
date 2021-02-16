/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/MenuDialog/MenuDialog.h"
#include "Enums/UIEnum/UIEnum.h"
#include "Structs/Secret/SecretCredential.h"
#include "GameInstanceUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameInstanceUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IGameInstanceUIInterface
{
	GENERATED_BODY()

public:
	virtual void OpenDialog(const EMenuDialog TypeOfDialog, class ISwitchableWidgetInterface* CurrentParent) = 0;
	virtual void CallUI(const EUIEnum UiToCall) = 0;
	virtual const bool TestSetup() const = 0;
	virtual bool GetNewProgressBarWidget(class UMonsterInformationWidget*& UMonsterInformationWidget) = 0;
	virtual class UActorMarkerWidget* AttachActorMarkerWidget(class AActor* Actor, UTexture2D* MarkerImage, bool IsMonster) = 0;
	virtual void ShowUIEntryMessageInformation() = 0;
	virtual void ShowUITutorialInformation(FText Title, FText Message, int32 index) = 0;
	virtual TArray<FSecretCredential> GetCredentials() const = 0;
	virtual TArray<int32> GetKnownSecretSloganIndices() const = 0;
	virtual void SetNoiseMultiplier(float Value) = 0;
	virtual void SetUIActive(bool IsActive) = 0;
	virtual void SetMapActive(bool IsActive) = 0;
	virtual class UCurrentScoreUserWidget* AddScoreWidget() = 0;


	virtual void SetScoreInGame(int32 ScoreInGame) = 0;
	virtual void SetMeatBonus(int32 MeatBonus) = 0;
	virtual void SetHungerBonus(int32 HungerBonus) = 0;
	virtual void SetFinishBonus(int32 FinishBonus) = 0;
	virtual void SetPickupBonus(int32 PickupBonus) = 0;
	virtual void SetFinalScore(int32 FinalScore) = 0;
	virtual void ShowFinalScore() = 0;
	virtual TArray<float> GetFinalMonsterHungerAverages() const = 0;
	virtual void ShowPickupWidget(bool Show) = 0;
	virtual void CallHideHighscore() = 0;
	virtual void CallShowHighscore() = 0;
	virtual void AddHighScoreEntry(FString Name) = 0;
	virtual void SetTrapBarValue(float Value) = 0;
	virtual void ResetTrapBar() = 0;
	virtual void ShowTrapBar() = 0;
};
