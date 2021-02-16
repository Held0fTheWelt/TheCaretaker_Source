/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Time/TimeInformationWidget.h"

#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Structs/TimeSet/TimeSet.h"
#include "Misc/Timespan.h"

void UTimeInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameMode ! This shouldn't happen !")
	}
	else
	{
		SetTime(GameModeInterface->GetCurrentTime());
	}
}

void UTimeInformationWidget::SetTime(const FTimeSet &Time)
{	
	FNumberFormattingOptions FormattingOptions;
	FormattingOptions.MinimumIntegralDigits = 2;
	FormattingOptions.MaximumIntegralDigits = 2;
	FormattingOptions.MinimumFractionalDigits = 0;
	FormattingOptions.MaximumFractionalDigits = 0;
	Hour->SetText(FText::AsNumber(Time.Hour, &FormattingOptions));
	Minute->SetText(FText::AsNumber(Time.Minute, &FormattingOptions));	
}
