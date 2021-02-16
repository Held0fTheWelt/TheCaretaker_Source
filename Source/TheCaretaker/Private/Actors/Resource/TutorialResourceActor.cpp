/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TutorialResourceActor.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ATutorialResourceActor::ATutorialResourceActor()
{
	IndexInTutorial = 0;
}

void ATutorialResourceActor::BeginPlay()
{
	Super::BeginPlay();

	TutorialGameMode = Cast<ITutorialInterface> (UGameplayStatics::GetGameMode(GetWorld()));
}

void ATutorialResourceActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (TutorialGameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Tutorial GameMode Interface. This shouldn't happen !")
	}
	else
	{
		if (TutorialGameMode->GetCurrentTutorialIndex() == IndexInTutorial)
		{
			Super::LeftMouseButtonClicked(CollectableRef);
			if (ResourceType != EResourceType::RT_MEAT)
			{
				TutorialGameMode->SetNextIndex();
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
