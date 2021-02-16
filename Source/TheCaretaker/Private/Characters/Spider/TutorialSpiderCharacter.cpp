/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TutorialSpiderCharacter.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ATutorialSpiderCharacter::ATutorialSpiderCharacter()
{
	IndexInTutorial = 0;
}

void ATutorialSpiderCharacter::BeginPlay()
{
	Super::BeginPlay();

	TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ATutorialSpiderCharacter::NotifyOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		return;
	}

	if (TutorialGameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Tutorial GameMode Interface. This shouldn't happen !")
	}
	else
	{
		if (TutorialGameMode->GetCurrentTutorialIndex() == IndexInTutorial)
		{			
			TutorialGameMode->SetNextIndex();
		}
		else
		{
			//TutorialGameMode->CommitFalseMessage(TutorialInformation[TutorialGameMode->GetCurrentTutorialIndex()].TextToShow);
		}
	}
}