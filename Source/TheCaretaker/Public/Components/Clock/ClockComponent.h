/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interfaces/Clock/ClockInterface.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "GameFunctionsInterface.h"
#include "Structs/TimeSet/TimeSet.h"
#include "ClockComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THECARETAKER_API UClockComponent : public USceneComponent, public IGameFunctionsInterface, public IPauseGameInterface, public IClockInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClockComponent();

	void SetTimeWidget(class UTimeInformationWidget* Widget);

protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Clock")
	FTimeSet TimeLimits;

	UPROPERTY(EditDefaultsOnly, Category = "Clock")
	FTimeSet StartTime;
	
	UPROPERTY(EditDefaultsOnly, Category = "Clock")
	FTimeSet EndTime;

	UPROPERTY(EditDefaultsOnly, Category = "Clock")
	int32 PlayedHours;

	UPROPERTY(VisibleAnywhere, Category = "Clock")
	FTimeSet CurrentTime;
		
	UPROPERTY(VisibleAnywhere, Category = "Clock")
	bool bRunningBackwards;

	// How many minutes woll be shown per hour. 4 = 0, 15, 30, 45
	UPROPERTY(EditDefaultsOnly, Category = "Clock")
	uint8 CalculatedMinutesPerHour;

	// Starts/Stops the clock
	UPROPERTY(VisibleAnywhere, Category = "Clock")
	bool bStartStop;

	class UTimeInformationWidget* TimeWidget;

	UPROPERTY(VisibleAnywhere, Category = "Clock")
	bool bPaused;
protected:
	UFUNCTION(Category = "Clock Actions", BlueprintImplementableEvent, BlueprintCallable)
	void UpdateTimeInBlueprint(FTimeSet& CurrentGameTime);
public :
	// Geerbt über IGameFunctionsInterface
	virtual void StopGame() override;
	void CallWinConditionUpdate();
	virtual void NewGame() override;
	void SetEndTime(int32 PlayedHours, FTimeSet EndTime);
	void UpdateClockSettings();

private:
	FTimerHandle TimerHandle_ClockComponent;

	void ClockTick();

	int32 UpdateIntervalValue(float Current, float Interval);
	void UpdateDayChange();

	void CalculateLastIntervalCount();

private:
	UPROPERTY(VisibleAnywhere, Category = "Clock")
	float MinutesPerSecond;

	UPROPERTY(VisibleAnywhere, Category = "Clock")
	float ClockTimeShift;
		
	UPROPERTY(VisibleAnywhere, Category = "Clock")
	int32 StartIntervalCount;

	UPROPERTY(VisibleAnywhere, Category = "Clock")
	int32 CurrentIntervalCount;

	UPROPERTY(VisibleAnywhere, Category = "Clock")
	int32 LastIntervalCount;

	UPROPERTY(VisibleAnywhere, Category = "Clock")
	int32 MinutesPerInterval;


	bool bFirstRun;
public:
	// How long lasts a day in realtime seconds. 1440 = 24 minutes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Clock")
	float TimePerDay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	float CurrentRealTime;

	// Inherited via IPauseGameInterface
	virtual void SetGamePaused(bool SetGamePaused) override;
	virtual bool IsPaused() const;
	virtual bool IsTimeUp() const;

	float CurrentTimeValue() const;

	void SetCurrentTimeToMidnight();
	void TimeRunningBackwards(bool SetActive);

	FTimeSet GetCurrentTime();

	// Inherited via IClockInterface
	virtual float GetCurrentTime() const override;
	virtual float GetMaxTime() const override;
};
