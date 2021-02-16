/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericProgressBarWidget.generated.h"

/** General ProgressBar to show Progress */
UCLASS()
class THECARETAKER_API UGenericProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Progress bar to show progress of sth.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UProgressBar* ProgressBar;

public:
	// Shows or hides the progress Bar
	UFUNCTION(BlueprintCallable, Category = "ProgressBar")
	virtual void SetProgressBarVisibility(bool Show);

	// Resets the progress bar and sets visibility to hidden
	UFUNCTION(BlueprintCallable, Category = "ProgressBar")
	virtual void ResetProgressBar();

	// Value is between 0 and 1.0 !!!
	UFUNCTION(BlueprintCallable, Category = "ProgressBar")
	virtual void SetProgressBarPercentage(float Percentage);
};
