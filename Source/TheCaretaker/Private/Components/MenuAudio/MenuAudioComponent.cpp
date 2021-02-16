/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "MenuAudioComponent.h"

#include "TimerManager.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameMode/Menu/MenuGameModeInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Log/GlobalLog.h"

FMenuAudioClip::FMenuAudioClip()
{
	AudioClip = nullptr;
	LevelPointsNeeded = 0;
	bIsPart2 = false;
}

UMenuAudioComponent::UMenuAudioComponent()
{
	AudioClipSettings = TArray<FMenuAudioClip>();
	CompetitionSoundtrack = TArray<USoundBase*>();
}

void UMenuAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AudioClipSettings.Num() == 0)
	{
		LOG_WARNING(InitializationLog, "AudioClipSetting was empty. Is it setup in the Menu GameModes component settings?")
	}
	else
	{
		GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen!")
		}
		else
		{
			//if (GameInstance->IsCompeteAccessible())
			//{
			//	if (CompetitionSoundtrack.Num() > 0)
			//	{
			//		Sound = CompetitionSoundtrack[0];
			//		Play();
			//		FTimerHandle TimerHandle;
			//		
			//		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMenuAudioComponent::ContinueCompetition, Sound->Duration, false);
			//	}
			//}
			//else
			//{
				int32 LevelPoints = GameInstance->GetCurrentLevelPoints();
				bool IsPart2 = GameInstance->IsPart2();

				TArray<FMenuAudioClip> TempList = TArray<FMenuAudioClip>();

				for (auto ClipInformation : AudioClipSettings)
				{
					if (ClipInformation.bIsPart2 == IsPart2)
					{
						TempList.Add(ClipInformation);
					}
				}

				for (auto ClipInformation : TempList)
				{
					if (LevelPoints < ClipInformation.LevelPointsNeeded)
					{
						break;
					}

					Sound = ClipInformation.AudioClip;
				}
				Play();
			//}
		}
	}
}

void UMenuAudioComponent::ContinueCompetition()
{
	//if (CompetitionSoundtrack.Num() > 1)
	//{
	//	if (CompetitionSoundtrack[1] != nullptr)
	//	{
	//		Sound = CompetitionSoundtrack[1];
	//		Play();
	//	}
	//}
}
