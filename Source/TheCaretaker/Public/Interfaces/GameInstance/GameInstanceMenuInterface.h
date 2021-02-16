/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/MenuDialog/MenuDialog.h"
#include "Enums/UIEnum/UIEnum.h"
#include "Enums/Achievement/AchievementType.h"
#include "UObject/Interface.h"
#include "Enums/IngameMenuCall/IngameMenuCall.h"
#include "GameInstanceMenuInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameInstanceMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/** Functions a GameInstance is called by some menu out there */
class THECARETAKER_API IGameInstanceMenuInterface
{
	GENERATED_BODY()
			
public:
	virtual bool HasPartAchieved(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) const = 0;
	virtual void ShowLoadLevel() = 0;
	virtual void LoadLevelFinished() = 0;
	virtual void RestartLevel() = 0;
	virtual void SaveGameData() = 0;
	virtual void Quit() = 0;
	virtual bool IsPartTwo() const = 0;

	virtual void CloseIngameMenu() = 0;
	virtual void OpenIngameMenu(EIngameMenuCall MenuCall) = 0;
	virtual void HideUnwantedUIElementsOnFinish() = 0;
	
	virtual void NewGame() = 0;
	virtual void OpenMap(FName &MapName) = 0;
	virtual void PerformLevelChange() = 0;
	virtual void ContinueForced() = 0;
	virtual void OpenMenuMap() = 0;
	virtual void TutorialFinished() = 0;

	virtual class AGameMode_Menu* GetMenuGameMode() = 0;
	virtual bool CompletedCurrentLevel() = 0;

	virtual void ShowNewCredentials() = 0;

	virtual void Default() = 0;
	virtual void Classic() = 0;
	virtual void HideWinInformation() = 0;

	virtual void HideFinalScore() = 0;

	virtual void CountAchievement(EAchievementType AchievementType) = 0;
	virtual bool IsCaretakerOne() const = 0;
};
