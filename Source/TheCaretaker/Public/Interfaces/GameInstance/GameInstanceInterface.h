/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/Level/LevelInformation.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "GameInstanceInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API IGameInstanceInterface
{
	GENERATED_BODY()

public:
	virtual class UMainUI* GetGameUI() = 0;
	virtual TArray<FLevelInformation> GetGameInformation() const = 0;
	virtual void ResetTestModes() = 0;
	virtual void ResetPlayModes() = 0;
	virtual bool TestCredentials(FString Credentials) = 0;
	virtual void RecalculateCurrentProgress() = 0;
	virtual void UpdateGameStateValues() = 0;
	virtual void TestExtraLevelsSetup() = 0;
	virtual void CheckSecretMessageTypedIn(const FText& Text) = 0;
	virtual void TestCompetitionMode() = 0;
};
