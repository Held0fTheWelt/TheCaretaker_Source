/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/GameSecrets/GameSecrets.h"

FGameSecret::FGameSecret()
{
	GameSecret = EGameSecretsEnum::GS_NONE;
	bIsActive = false;
	AchievementTitle = FText();
	AchievementMessage = FText();
}

FGameSecret::FGameSecret(EGameSecretsEnum Type)
{
	GameSecret = Type;
	bIsActive = false;
	AchievementTitle = FText();
	AchievementMessage = FText();
}

FGameSecrets::FGameSecrets()
{
	Secrets.Add(FGameSecret(EGameSecretsEnum::GS_PICKUPS));
	Secrets.Add(FGameSecret(EGameSecretsEnum::GS_MORETHANTHREE));
	Secrets.Add(FGameSecret(EGameSecretsEnum::GS_PLAYYVESONCE));
}
