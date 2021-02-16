/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"
#include "MonsterHungerBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMonsterHungerBarWidget : public UGenericProgressBarWidget, public IPauseGameInterface
{
	GENERATED_BODY()
	
public:
	UMonsterHungerBarWidget();

	virtual void NativeOnInitialized();

public:
	// Progress bar to show progress of sth.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UImage* MonsterImage;

	UPROPERTY(EditAnywhere, Category = "MonsterImage")
	class UTexture2D* MonsterTexture;
	

	UPROPERTY(EditAnywhere, Category = "Margin")
	float MarginTop;
	UPROPERTY(EditAnywhere, Category = "Margin")
	float MarginMultiplier;
private:
	UPROPERTY(VisibleAnywhere, Category = "Multiplier")
	float ProgressBarMultiplier;

	UPROPERTY(VisibleAnywhere, Category = "Pause")
	bool bPaused;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Margin")
	float CurrentPosition;
public:
	void SetMonsterImage(class UTexture2D* Image);

	// Shows or hides the progress Bar
	virtual void SetProgressBarVisibility(bool Show) override;

	// Resets the progress bar and sets visibility to hidden	
	virtual void ResetProgressBar() override;

	// Value is between 0 and 1.0 !!!
	virtual void SetProgressBarPercentage(float Percentage) override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

	// Inherited via IPauseGameInterface
	virtual void SetGamePaused(bool SetGamePaused) override;

	virtual bool IsPaused() const;

};
