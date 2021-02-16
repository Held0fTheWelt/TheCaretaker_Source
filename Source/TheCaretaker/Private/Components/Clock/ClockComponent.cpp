/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Components/Clock/ClockComponent.h"

#include "TimerManager.h"

#include "Engine/World.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/WinCondition/WinConditionVolumeInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Widgets/Time/TimeInformationWidget.h"

#pragma region Constructor
UClockComponent::UClockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TimeLimits.Hour = 24;
	TimeLimits.Minute = 60;
	TimeLimits.Seconds = 60;

	StartTime.Hour = 0;
	StartTime.Minute = 0;
	StartTime.Seconds = 0;

	EndTime.Hour = 23;
	EndTime.Minute = 59;
	EndTime.Seconds = 59;

	PlayedHours = 10;

	TimePerDay = 1440;
	CalculatedMinutesPerHour = 4;
	
	bStartStop = false;

	MinutesPerSecond = 0;
	ClockTimeShift = 0;
	CurrentIntervalCount = 0;
	MinutesPerInterval = 0;
	CurrentRealTime = 0;
	StartIntervalCount = 0;

	bRunningBackwards = false;
}
#pragma endregion

#pragma region Set Time Widget
void UClockComponent::SetTimeWidget(UTimeInformationWidget* Widget)
{
	if (Widget == nullptr)
	{
		LOG_WARNING(InitializationLog, "Timeinformation widget was null while initializing ClockComponent");
		return;
	}
	TimeWidget = Widget;
}
#pragma endregion

#pragma region Begin Play
void UClockComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateClockSettings();
}
#pragma endregion

#pragma region TickComponent
void UClockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bStartStop == false)
		return;

	if (bFirstRun)
	{
		CurrentRealTime += GetWorld()->GetDeltaSeconds();
		CurrentRealTime = 0;
		bFirstRun = false;
	}
	else
	{
		if (bRunningBackwards)
		{
			//LOG_WARNING(RuntimeExecutionLog, "Running Backwards")
				CurrentRealTime -= GetWorld()->GetDeltaSeconds();
		}
		else
		{
			CurrentRealTime += GetWorld()->GetDeltaSeconds();
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Current Realtime: %f"), CurrentRealTime);

	CurrentIntervalCount = UpdateIntervalValue(CurrentRealTime, ClockTimeShift) + StartIntervalCount;

	CurrentTime.Hour = CurrentIntervalCount / CalculatedMinutesPerHour;

	CurrentTime.Minute = (CurrentIntervalCount % CalculatedMinutesPerHour) * MinutesPerInterval;

	UpdateDayChange();

	if (CurrentIntervalCount >= LastIntervalCount)
	{
		UE_LOG(LogTemp, Display, TEXT("Clock Time is Up! Stopping clock !"));
		CallWinConditionUpdate();
		StopGame();
	}

	TimeWidget->SetTime(CurrentTime);

	// Make some blueprint things, if needed
	UpdateTimeInBlueprint(CurrentTime);

}
#pragma endregion

#pragma region Stop Game
void UClockComponent::StopGame()
{
	bStartStop = false;


}
#pragma endregion
void UClockComponent::CallWinConditionUpdate()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UWinConditionVolumeInterface::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		IWinConditionVolumeInterface* WinConditionVolume = Cast<IWinConditionVolumeInterface>(Actor);

		if (WinConditionVolume != nullptr)
		{
			WinConditionVolume->CallWinConditionUpdate();
			// only do this once
			break;
		}

	}
}

#pragma region New Game
void UClockComponent::NewGame()
{
	// Safety Reasons
	StopGame();

	bStartStop = true;
	bFirstRun = true;	
}
#pragma endregion

void UClockComponent::SetEndTime(int32 NewPlayedHours, FTimeSet NewEndTime)
{
	PlayedHours = NewPlayedHours;
	EndTime = NewEndTime;
}

void UClockComponent::UpdateClockSettings()
{
	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
	}
	else
	{
		FClockSetup ClockSetup = GameInstance->GetClockSetup();

		TimePerDay /= ClockSetup.ClockModifier;
	}

	CurrentTime.Hour = StartTime.Hour;
	CurrentTime.Minute = StartTime.Minute;

	// Calculate the minutes each real time second values
	MinutesPerSecond = (TimeLimits.Hour * TimeLimits.Minute * TimeLimits.Seconds) / (TimePerDay * 59.99794322085292);

	// Calculate the amount of time needed to switch the clock
	ClockTimeShift = (TimeLimits.Minute / CalculatedMinutesPerHour) / MinutesPerSecond;

	// This is the number, each interval adds up in minutes
	MinutesPerInterval = TimeLimits.Minute / CalculatedMinutesPerHour;

	// 
	CurrentIntervalCount = StartTime.Hour * CalculatedMinutesPerHour + StartTime.Minute % MinutesPerInterval;
	StartIntervalCount = CurrentIntervalCount;

	CalculateLastIntervalCount();

	CurrentRealTime = 0;
	bRunningBackwards = false;
}

#pragma region Clock Tick
void UClockComponent::ClockTick()
{
	
	
}
#pragma endregion

#pragma region Update Interval Value
int32 UClockComponent::UpdateIntervalValue(float Current, float Interval)
{
	return Current / Interval;
}
#pragma endregion

#pragma region Update Day Change
void UClockComponent::UpdateDayChange()
{
	if (CurrentTime.Hour >= TimeLimits.Hour)
	{
		CurrentTime.Hour %= TimeLimits.Hour;
	}
}
#pragma endregion

#pragma region Calculate Last Interval Count
void UClockComponent::CalculateLastIntervalCount()
{
	if (StartTime.Hour == EndTime.Hour && StartTime.Minute == EndTime.Minute)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartTime mustn't be EndTime. Clock will not run this way!"));
		return;
	}

	if (StartTime.Hour <= EndTime.Hour && StartTime.Minute < EndTime.Minute)
	{
		LastIntervalCount = EndTime.Hour * CalculatedMinutesPerHour + EndTime.Minute % MinutesPerInterval;
	}
	else
	{
		LastIntervalCount = EndTime.Hour * CalculatedMinutesPerHour + EndTime.Minute % MinutesPerInterval + TimeLimits.Hour * CalculatedMinutesPerHour;
	}
}
#pragma endregion
void UClockComponent::SetGamePaused(bool SetGamePaused)
{
	bStartStop = SetGamePaused;
}
bool UClockComponent::IsPaused()const
{
	return bStartStop;
}
bool UClockComponent::IsTimeUp() const
{
	return CurrentIntervalCount >= LastIntervalCount;
}

float UClockComponent::CurrentTimeValue() const
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentRealTime / (TimePerDay / 2.4f));
	return  CurrentRealTime;
}

void UClockComponent::SetCurrentTimeToMidnight()
{
	bFirstRun = true;
}

void UClockComponent::TimeRunningBackwards(bool Backwards)
{
	bRunningBackwards = Backwards;	
}

FTimeSet UClockComponent::GetCurrentTime()
{
	CurrentIntervalCount = UpdateIntervalValue(CurrentRealTime, ClockTimeShift) + StartIntervalCount;

	CurrentTime.Hour = CurrentIntervalCount / CalculatedMinutesPerHour;

	CurrentTime.Minute = (CurrentIntervalCount % CalculatedMinutesPerHour) * MinutesPerInterval;

	UpdateDayChange();

	UpdateTimeInBlueprint(CurrentTime);

	return CurrentTime;
}

float UClockComponent::GetCurrentTime() const
{
	return CurrentRealTime;
}

float UClockComponent::GetMaxTime() const
{
	return TimePerDay / TimeLimits.Hour * PlayedHours;
}
