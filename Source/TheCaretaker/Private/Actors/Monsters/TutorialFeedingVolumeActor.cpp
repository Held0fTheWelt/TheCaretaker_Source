/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TutorialFeedingVolumeActor.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Game/CaretakerGameState.h"

ATutorialFeedingVolumeActor::ATutorialFeedingVolumeActor()
{
	IndexInTutorial = 0;
}

void ATutorialFeedingVolumeActor::InitMarkerWidget()
{
	TArray<AActor*> Actors;
	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerGameState::StaticClass(), Actors);
	for (const auto& Actor : Actors) {

		ACaretakerGameState* GameStateActor = Cast<ACaretakerGameState>(Actor);
		if (GameStateActor != nullptr)
		{
			MonsterStatus.AddDynamic(GameStateActor, &ACaretakerGameState::MonsterReport);
		}
	}
}

void ATutorialFeedingVolumeActor::BeginPlay()
{
	Super::BeginPlay();

	TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ATutorialFeedingVolumeActor::MonsterFed()
{
	Super::MonsterFed();

	TutorialGameMode->SetNextIndex();
}

void ATutorialFeedingVolumeActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
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
