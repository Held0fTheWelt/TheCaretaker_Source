/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TutorialGarbageActor.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Player/CaretakerPlayerState.h"

ATutorialGarbageActor::ATutorialGarbageActor()
{
	IndexInTutorial = 0;
}

void ATutorialGarbageActor::BeginPlay()
{
	Super::BeginPlay();

	TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	PlayerState = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ACaretakerPlayerState>();
}

void ATutorialGarbageActor::LeftMouseClicked()
{
	if (TutorialGameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Tutorial GameMode Interface. This shouldn't happen !")
	}
	else
	{
		if (TutorialGameMode->GetCurrentTutorialIndex() == IndexInTutorial)
		{
			Super::LeftMouseClicked();
			TutorialGameMode->SetNextIndex();
		}
		else
		{
			if (TutorialGameMode->GetCurrentTutorialIndex() <= TutorialInformation.Num() - 1)
			{
				TutorialGameMode->CommitFalseMessage(TutorialInformation[TutorialGameMode->GetCurrentTutorialIndex()].TextToShow);
			}
			else
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not find index for message");
			}
		}
	}
}
