/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "CurrentScoreUserWidget.h"

#include "TimerManager.h"

#include "Engine/World.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

UCurrentScoreUserWidget::UCurrentScoreUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	VisualScore = 0;
	CurrentScore = 0;
	ScoreAddition1Value = 0;
	ScoreAddition2Value = 0;
	ScoreAddition3Value = 0;
	ShowDelay = 2.f;
	ShowScoreMultiplier = 1000.f;
	CurrentShowDelay = 0.f;
	TimeToShowScoreAddition = 3.5f;

	TimeToWaitForScoreAddedSound = 2.f;
	NewScoreSound = nullptr;
	SoundAddingScore = nullptr;
	SoundAddedScore = nullptr;

	bFinishSoundPlayed = true;



	//ScoreAdditionAudioComponent->SetupAttachment(this);
}

void UCurrentScoreUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(InitializationLog,"Could not cast GameMode to Interface ! This shouldn't happen !")
	}
	else
	{
		GameModeInterface->AddScoreSound(SoundAddingScore);
	}
}

void UCurrentScoreUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentScore > VisualScore)
	{
		if (CurrentShowDelay < ShowDelay)
		{
			bFinishSoundPlayed = false;
			CurrentShowDelay += InDeltaTime;
		}
		else
		{
			VisualScore += InDeltaTime * ShowScoreMultiplier;
			if (GameModeInterface == nullptr)
			{
				LOG_WARNING(InitializationLog, "Could not cast GameMode to Interface ! This shouldn't happen !")
			}
			else
			{
				GameModeInterface->PlayScoreSound(true);
			}
		}
	}
	else
	{
		if (GameModeInterface == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast GameMode to Interface ! This shouldn't happen !")
		}
		else
		{
			GameModeInterface->PlayScoreSound(false);
		}
		if (bFinishSoundPlayed == false)
		{
			if (SoundAddedScore == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog,"Could not play Score Added Sound, because it was null. Is it set in the widget blueprint ?")
			}
			else
			{
				FTimerHandle TimerHandle;
				FTimerDelegate Delegate;
				Delegate.BindLambda([=] { 
					UGameplayStatics::PlaySound2D(GetWorld(), SoundAddedScore);
					});
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeToWaitForScoreAddedSound, false);
			}
			bFinishSoundPlayed = true;
		}
		CurrentShowDelay = 0.f;
		if (VisualScore > CurrentScore)
		{
			VisualScore = CurrentScore;
		}
	}
}

void UCurrentScoreUserWidget::SetNewScore(int32 NewScore, int32 NewAddedScore)
{
	if (bAddition1IsLocked == false)
	{
		ScoreAddition1Value = NewAddedScore;
		ShowAddedScoreImplementation(0);
		bAddition1IsLocked = true;
		FTimerHandle TimerHandle;
		//delegate function to be called when timer finishes
		//bind a lambda function to the delegate
		FTimerDelegate Delegate;
		Delegate.BindLambda([=] { bAddition1IsLocked = false; });
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeToShowScoreAddition, false);
	}
	else if (bAddition2IsLocked == false)
	{
		ScoreAddition2Value = NewAddedScore;
		ShowAddedScoreImplementation(1);
		bAddition2IsLocked = true;
		FTimerHandle TimerHandle;
		FTimerDelegate Delegate;
		Delegate.BindLambda([=] { bAddition2IsLocked = false; });
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeToShowScoreAddition, false);
	}
	else if (bAddition3IsLocked == false)
	{
		ScoreAddition3Value = NewAddedScore;
		ShowAddedScoreImplementation(2);
		bAddition3IsLocked = true;
		FTimerHandle TimerHandle;
		FTimerDelegate Delegate;
		Delegate.BindLambda([=] { bAddition3IsLocked = false; });
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeToShowScoreAddition, false);
	}
	else if (bAddition4IsLocked == false)
	{
		ScoreAddition4Value = NewAddedScore;
		ShowAddedScoreImplementation(3);
		bAddition4IsLocked = true;
		FTimerHandle TimerHandle;
		FTimerDelegate Delegate;
		Delegate.BindLambda([=] { bAddition4IsLocked = false; });
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeToShowScoreAddition, false);
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog,"No more ScoreAddition Slots ! 5 in a row shouldn't happen ....")
	}
	UE_LOG(LogTemp, Warning, TEXT("Score Added: %d"), NewAddedScore);

	CurrentScore = NewScore;
	if (NewScoreSound == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot play New Score sound, because it is null. Is the variable setup in the widget blueprint for current score ?")
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), NewScoreSound);
	}
}