/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Base/UserWidgetBase.h"
#include "Enums/PlayMode/PlayMode.h"
#include "StartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UStartMenuWidget : public UUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UStartMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* NewGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* Quit;

	UPROPERTY(meta = (BindWidget))
	class UButton* Options;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_NewGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* Tutorial;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayMode;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayModeText;

	UPROPERTY(meta = (BindWidget))
	class UButton* Credentials;

	UPROPERTY(meta = (BindWidget))
	class UButton* LoadGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Secret")
	FString CredentialsForPlaymodeButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "New Game Button")
	FText ContinueText;

	virtual void ShowWidget(bool Show) override;
	
	void SetAlternateTextToNewGameButton();
	   
	bool bShowPlayModeButton;
private:
	UFUNCTION()
	void CallNewGame();

	UFUNCTION()
	void CallOptionsDialog();

	UFUNCTION()
	void CallQuitGame();

private:
	UFUNCTION()
	void CallTutorial();
	
	UFUNCTION()
	void CallLevelSelector();

	UFUNCTION()
	void CallSwitchGameMode();

	UFUNCTION()
	void CallCredentialViewTable();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayMode")
	TArray<FText> PlayModes;
private:
	UPROPERTY()
	int8 CurrentPlayModeIndex;
};
