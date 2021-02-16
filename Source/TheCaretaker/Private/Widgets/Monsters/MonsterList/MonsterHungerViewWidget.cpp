/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Monsters/MonsterList/MonsterHungerViewWidget.h"

#include "FMODAudioComponent.h"

#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Engine/World.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Structs/FMOD/FMODParameterSetList.h"
#include "Widgets/Monsters/HungerBar/MonsterHungerBarWidget.h"
#include "Widgets/Monsters/MonsterInformationWidget.h"
#include "Widgets/Scores/CurrentScoreUserWidget.h"

UMonsterHungerViewWidget::UMonsterHungerViewWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FMODParameterName = EName::NAME_None;
	FMODParameterType = EFMODParameterType::FMOD_PT_MONSTER;
	FMODVolume = 1.f;
}

void UMonsterHungerViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IGameInstanceAccessoryInterface* Accessory = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	FMODParameterSet ParameterSet = Accessory->GetFMODParameterSet(FMODParameterType);
	
	FMODParameterName = ParameterSet.ParameterName;
	FMODVolume = ParameterSet.SoundChangeValue;

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

	if (GameModeBase == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not Get GameMode to construct MonsterHungerViewWidget ! This shouldn't happen !")
	}
	else
	{
		IGameModeInterface* GameMode = Cast<IGameModeInterface>(GameModeBase);
		if (GameMode == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not Cast GameMode to Caretaker GameMode. This shouldn't happen !")
		}
		else
		{
			MusicComponent = GameMode->GetFMODComponent();
		}
	}
}

void UMonsterHungerViewWidget::AddMonster(UMonsterInformationWidget* Monster)
{
	Monsters.Add(Monster);
}

void UMonsterHungerViewWidget::AddScoreWidget(UCurrentScoreUserWidget* ScoreWidget)
{
	if (ScoreWidget == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "ScoreWidget was null ! Cannot Add to Widget !")
	}
	else
	{
		MonsterList->AddChild(ScoreWidget);
	}
}

void UMonsterHungerViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float CurrentLevel = CalculateCurrentValues();

	SetFMODParameters(CurrentLevel);
}

float UMonsterHungerViewWidget::CalculateCurrentValues()
{
	float MaxValue = 0.f;

	for (auto Monster : Monsters)
	{
		float ThisMonster = Monster->MonsterHunger->ProgressBar->Percent;

		if (ThisMonster > MaxValue)
		{
			MaxValue = ThisMonster;
		}
	}

	return MaxValue;
}

void UMonsterHungerViewWidget::SetFMODParameters(float Value)
{
	if (FMODParameterName == EName::NAME_None)
	{
		LOG_WARNING(RuntimeLog, "Cannot Set FMOD Parameters, because ParameterName is not set.")
		return;
	}

	if (MusicComponent == nullptr)
	{
		LOG_WARNING(RuntimeLog, "Cannot Set FMOD Parameters, because MusicComponent was null. This shouldn't happen !")
	}
	else
	{
		if (Value >= 1.0f)
		{
			MusicComponent->SetParameter(FMODParameterName, FMODVolume);
		}
		else
		{
			MusicComponent->SetParameter(FMODParameterName, 0.0f);
		}
	}
}

TArray<UMonsterInformationWidget*> UMonsterHungerViewWidget::GetMonsters() const
{
	return Monsters;
}
