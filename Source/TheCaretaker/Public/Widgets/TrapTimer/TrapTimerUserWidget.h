/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "TrapTimerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UTrapTimerUserWidget : public UGenericProgressBarWidget, public IPauseGameInterface
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UImage* Background;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UImage* Bar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UTextBlock* Text;
public:
	UTrapTimerUserWidget();

	void SetTrapTimerValue(float Value);

	void SetTrapTimerColor(float Value);


	// Inherited via IPauseGameInterface
	virtual void SetGamePaused(bool SetGamePaused) override;

	virtual bool IsPaused() const override;

};
