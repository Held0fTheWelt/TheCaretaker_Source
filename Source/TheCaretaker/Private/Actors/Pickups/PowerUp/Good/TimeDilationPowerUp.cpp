/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TimeDilationPowerUp.h"

#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ATimeDilationPowerUp::ATimeDilationPowerUp()
{
	DilationValue = 2;
}

void ATimeDilationPowerUp::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	CharacterInterface = Cast<ICharacterInterface>(Character);
}

void ATimeDilationPowerUp::Expired()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	if (CharacterInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "CharacterInterface not found")
	}
	else
	{
		CharacterInterface->IsDilatingTime(1.f);
	}

	Super::Expired();
}
		

void ATimeDilationPowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f / DilationValue);

	if (CharacterInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "CharacterInterface not found")
	}
	else
	{
		CharacterInterface->IsDilatingTime(DilationValue);
	}

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
	}
	else
	{
		AchievementInstance->CountAchievement(EAchievementType::AT_PICKUP);
	}
}
