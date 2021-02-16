/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TutorialChestActor.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Player/CaretakerPlayerState.h"

ATutorialChestActor::ATutorialChestActor()
{
	IndexInTutorial = 0;
}

void ATutorialChestActor::BeginPlay()
{
	Super::BeginPlay();

	TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));
			
	PlayerState = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ACaretakerPlayerState>();
}

void ATutorialChestActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (TutorialGameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Tutorial GameMode Interface. This shouldn't happen !")
	}
	else
	{
		if (TutorialGameMode->GetCurrentTutorialIndex() == IndexInTutorial)
		{
			if (PlayerState == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not find PlayerState ! This shouldn't happen !")
			}
			else
			{
				if (PlayerState->GetGoldCount() == 1)
				{
					Super::LeftMouseButtonClicked(CollectableRef);
					TutorialGameMode->SetNextIndex();
				}
				else
				{

				}
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
