/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TutorialTrapActor.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ATutorialTrapActor::ATutorialTrapActor()
{
	IndexInTutorial = 0;
}

void ATutorialTrapActor::BeginPlay()
{
	Super::BeginPlay();

	TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ATutorialTrapActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (TutorialGameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Tutorial GameMode Interface. This shouldn't happen !")
	}
	else
	{
		if (TutorialGameMode->GetCurrentTutorialIndex() == IndexInTutorial)
		{
			if (!bIsArmed)
			{				
				Super::LeftMouseButtonClicked(CollectableRef);
			}
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

void ATutorialTrapActor::TrapSolved()
{
	Super::TrapSolved();

	TutorialGameMode->SetNextIndex();
}
