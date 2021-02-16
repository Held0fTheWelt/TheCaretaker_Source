/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/GameInstance.h"
#include "Enums/IngameMenuCall/IngameMenuCall.h"
#include "Enums/MenuDialog/MenuDialog.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Enums/UIEnum/UIEnum.h"
#include "Interfaces/GameInstance/GameInstanceInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/Widgets/SwitchToParent/SwitchableWidgetInterface.h"
#include "Structs/Achievement/Achievement.h"
#include "Structs/CurrentProgress/CurrentProgress.h"
#include "Structs/FMOD/FMODParameterSetList.h"
#include "Structs/FMOD/ModEventList.h"
#include "Structs/Maps/MapDefinition.h"
#include "Structs/Messages/CaretakerMessages.h"
#include "Structs/Level/LevelInformation.h"
#include "Structs/Pickup/PickupSpawnLocation.h"
#include "Structs/Secret/SecretSloganList.h"
#include "Structs/Secret/SecretConnection.h"
#include "Structs/PlayMode/PlayModeInformation.h"
#include "Structs/PlayMode/PlayModeModifierInformation.h"
#include "Structs/PowerUp/PowerUpList.h"
#include "GameInstanceManager.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FSpawnMarkerWidgetInformation
{
	GENERATED_BODY()

public:
	FSpawnMarkerWidgetInformation();
	FSpawnMarkerWidgetInformation(class AActor* Actor, class UTexture2D* Texture, bool IsMonster);

public:
	bool bIsMonster;
	class UTexture2D* Texture;
	class AActor* Actor;

};

//static FAutoConsoleCommandWithOutputDevice FLogSharedTargetCountCommand(
//	TEXT("r.Composure.CompositingElements.Debug.LogSharedTargetsCount"),
//	TEXT("Dumps the count of all target currently allocated for the shared target compositing target pool."),
//	FConsoleCommandWithOutputDeviceDelegate::CreateStatic(&ElementRenderTargetPool_Impl::LogSharedTargetCount));
/**
 * 
 */
UCLASS()
class THECARETAKER_API UGameInstanceManager : public UGameInstance, 
	public IGameInstanceInterface, 
	public IGameInstanceMenuInterface, 
	public IGameInstanceAccessoryInterface,
	public IGameInstanceUIInterface, 
	public IAchievementCountInterface
{
	GENERATED_BODY()

public:
	UGameInstanceManager(const FObjectInitializer& ObjectInitializer);

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init();

	void GetSavedPlayMode();
	
	bool IsPartTwoAchieved() const;

	UFUNCTION(BlueprintCallable)
	virtual bool IsPartTwo() const override;

protected:
	UPROPERTY()
	TSubclassOf<class APowerUp> CurrentPowerUpClass;
	
	UPROPERTY(EditDefaultsOnly)
	bool bIsCaretakerOne;

	UPROPERTY(SaveGame)
	TArray<FPickupSpawnLocation> PickupSpawnLocations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game | Setup | Pickup")
	TSubclassOf<class ASingleObjectPickup> CurrentPickUpClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game | Setup | Maps")
	FMapDefinition MapDefinition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game | Setup | Sound")
	FMODParameterSetList SoundDefinition;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Game | Setup | Sound")
	FMODEventList EventList;

	UPROPERTY(VisibleAnywhere, Category = "Game | Setup | Level Change")
	float LevelChangeDelay;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game | Information")
	class UDataTable* GameInformation;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game | Information")
	class UDataTable* ExtraLevelsGameInformation;
	
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game | Information")
	class UDataTable* LocalHighScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | PlayMode")
	class UDataTable* PlayModeInformationTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | PlayMode")
	class UDataTable* PlayModeInformationTableExtraLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | PlayMode")
	class UDataTable* PlayModeModifierInformationTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | PlayMode")
	class UDataTable* SecretCredentialList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | Score")
	class UDataTable* HighScoreDefinitionTable;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* PowerUpInformationTable;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FPowerUpList> PowerUpInformationList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Game | Pause")
	FCaretakerMessages Messages;

	FString ExtraLevelsDecryptKey;

	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlocked;
	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlockedToEarlyTitle;
	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlockedToEarlyGrats;
	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlockedToEarlyMessage;

	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlockedFailTitle;
	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlockedFailGrats;
	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FText SecretUnlockedFailMessage;
	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Score")
	int32 CompetitionSecretIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game | Save")
	TSubclassOf<class UTheCaretakerSaveGame> SaveGameTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Menu")
	TSubclassOf<class UUserWidget> MainMenuTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Menu")
	TSubclassOf<class UAdditionalMenuUserWidget> AdditionalMainMenuTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Menu| Options")
	TSubclassOf<class UUserWidgetBase> MainSettingsTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Menu| Options")
	TSubclassOf<class ULevelSelectionUserWidget> LevelSelectorBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Menu| Options")
	TSubclassOf<class UExtrasMenuUserWidget> CredentialsViewBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Game")
	TSubclassOf<class UMainUI> MainUiTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Menu")
	TSubclassOf<class UIngameMenuUserWidget> IngameMenuTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Monster")
	TSubclassOf<class UMonsterInformationWidget> MonsterInformationTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Monster")
	TSubclassOf<class UActorMarkerWidget> ActorMarkerTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | Score")
	TSubclassOf<class UCurrentScoreUserWidget> CurrentScoreBlueprint;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game ")
	FCurrentProgress CurrentProgress;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Diagnosis | Game ")
	class UTheCaretakerSaveGame* SaveGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Diagnosis | UI | Menu")
	class UMainMenuWidget* MenuUI;

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | UI | Menu")
	class UUserWidgetBase* OptionsWidget;

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | UI | Menu")
	class UUserWidgetBase* LevelSelector;

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | UI | Menu")
	class UUserWidgetBase* CredentialsView;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Diagnosis | UI | Game")
	class UMainUI* MainUI;

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | UI | Game")
	class UIngameMenuUserWidget* IngameMenu;
		
	TArray<FLevelInformation> LevelInformation;

	const FString SaveGameName = "SaveGame";

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | PlayMode")
	EPlayMode PlayMode;

	UPROPERTY(VisibleAnywhere, SaveGame, Category = "Diagnosis | PlayMode")
	EPlayMode PlayModeExtraModifier;

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | PlayMode")
	EPlayPath PlayPath;

	UPROPERTY(VisibleAnywhere, SaveGame, Category = "Diagnosis | PlayMode")
	TArray<FPlayModeInformation> PlayModeInformation;

	UPROPERTY(VisibleAnywhere, Category = "Diagnosis | PlayMode")
	TArray<FPlayModeModifierInformation> PlayModeModifiers;

	UPROPERTY(EditDefaultsOnly, Category = "Reload | Menu")
	float TimeToWaitForReloadMenu;

	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Secret")
	FSecretSloganList SecretSlogans;

	UPROPERTY(EditDefaultsOnly, Category = "Game | Setup | Difficulties")
	int32 MaxCountOfDifficulties;
public:
		
	virtual TArray<FLevelInformation> GetGameInformation() const override;
	virtual class IGameStateInterface* GetGameState() override;
	virtual TArray<FLevelInformation> GetLevelInformation() const override;
	virtual UMainUI* GetGameUI();
	virtual TArray<FAchievementDefinition> GetAchievements() override;
	virtual FAchievementLoadIdentifier GetLoadIdentifier() override;
	virtual TArray<FAchieved> GetAchievedRewards() override;
	virtual FMODParameterSet GetFMODParameterSet(EFMODParameterType ParameterType) override;
	virtual bool TestCredentials(FString Credentials) override;
	virtual void PerformLevelChange() override;

	bool CountCurrentProgress();

	virtual void SetCurrentDungeonPartInfos(int32 NewCurrentLevel, int32 NewCurrentDungeon, TEnumAsByte<EPartInformation> NewCurrentPart) override;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual FName GetMenuLevelName() const override;
	virtual FName GetTutorialLevelName() const override;
	virtual void SetCurrentLevelName(FName NewLevelName) override;
	virtual FName GetCurrentLevelName() const override;
	
	int32 GetCurrentLevel() const;
	int32 GetCurrentDungeon() const;
	int32 GetCurrentDifficulty() const;
	EPartInformation GetCurrentPart() const;

	UFUNCTION(BlueprintCallable, Category = "Mouse Events")
	void SetMouseEvents(bool On);

	UFUNCTION(BlueprintCallable, Category = "Pause")
	void SetPauseMode(bool Pause);

	UFUNCTION(BlueprintCallable, Category = "Trailer")
	bool GetPlayYvesOnce();

	UFUNCTION(BlueprintCallable, Category = "Trailer")
	void SetPlayYvesOnce(bool PlayedOnce);

public:
	UFUNCTION(BlueprintCallable, Category = "Achievements")
	int32 GetCurrentLevelPoints() const;

	virtual void NewGame() override;
	virtual void ShowLoadLevel() override;
	UFUNCTION(BlueprintCallable, Category = "Load Level")
	virtual void LoadLevelFinished();
	virtual void RestartLevel() override;
	UFUNCTION(BlueprintCallable)
	virtual void OpenIngameMenu(EIngameMenuCall MenuCall) override;
	UFUNCTION(BlueprintCallable)
	virtual void CloseIngameMenu() override;
	virtual void SaveGameData() override;
	UFUNCTION(Exec, BlueprintCallable)
	virtual void Quit() override;
	

	virtual void OpenMap(FName& MapName) override;
	
	UFUNCTION(Exec)
	void PlayYvesAgain();
	UFUNCTION(Exec)
	void Reboot();
	
	UFUNCTION(Exec)
	void Update(int32 UpdateState);

private:
	const bool LoadLevelInformation();
	const bool LoadPlayModeInformation();
	const bool LoadPlayModeModifierInformation();
	const bool LoadCredentialSetup();
	const bool LoadPowerUpSetup();
	virtual const bool TestSetup() const override;
	void DoesSaveGameExist();
	void SetupSaveGameData();
	void LoadRawSaveGame();
	void EmptyWidgets();
	virtual bool CompletedCurrentLevel() override;
	void CalculateCurrentLevelPoints();
	void RecalculateCurrentProgress();
	void UpdateCurrentProgress();
	UFUNCTION()
	void AchieveProgress();

public:
	virtual void OpenDialog(const EMenuDialog TypeOfDialog, ISwitchableWidgetInterface* CurrentParent) override;
	virtual void CallUI(const EUIEnum UiToCall);
	virtual bool GetNewProgressBarWidget(class UMonsterInformationWidget* &MonsterInformation) override;
	virtual class UActorMarkerWidget* AttachActorMarkerWidget(AActor* Actor, UTexture2D* MarkerImage, bool IsMonster) override;
private:
	TArray<FSpawnMarkerWidgetInformation> TempMarkerInfo;
	void CreateNewUserWidget(const EMenuDialog TypeOfDialog, ISwitchableWidgetInterface* CurrentParent);

public:
	virtual void CountAchievement(EAchievementType AchievementType);

	virtual bool IsSecretAccessible(FString SecretCode) override;

	virtual void UpdateHighScoreWidget(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) override;
protected:
	void LoadSaveGame();
private:
	void TestAchievements(EAchievementType AchievementType, int32 CurrentCount);
	/*bool LoadRawSaveGame(const FString& SaveGameName);*/
	void DumpSaveGame();
	void PerformLevelChangeDelay();
	FTimerHandle TimerHandle_LevelChangeDelay;
	void AcceptPlayMode();

	// Inherited via IGameInstanceMenuInterface
	virtual AGameMode_Menu* GetMenuGameMode()  override;

	UFUNCTION(Exec)
	void FullProgress();
	UFUNCTION(Exec)
	void ResetProgress();
	UFUNCTION(Exec)
	void SetProgress(int32 Level, int32 Dungeon, int32 Part, int32 Difficulty);
	
	UFUNCTION(Exec)
	void SetGameInformation(int32 Level, int32 Dungeon, int32 Part, int32 NumChests, int32 NumTraps, int32 NumGarbage);
	
	UFUNCTION(Exec)
	void PlayRandomMusicTitle();
	UFUNCTION(Exec)
	void PlayMusicTitle(int8 Title);
	
	UFUNCTION(Exec)
	void UltraSpeed();
	UFUNCTION(Exec)
	void SetWalkSpeed(float Speed);

	UFUNCTION(Exec)
	void Crazy();
	UFUNCTION(Exec)
	virtual void Default() override;
	UFUNCTION(Exec)
	void Lazy();
	UFUNCTION(Exec)
	virtual void Classic() override;
	
	UFUNCTION(Exec)
	void ShowSpiderWebs(int32 OnOff);

	UFUNCTION(Exec)
	void ShowGameStats(bool On);
		
	UFUNCTION(Exec)
	void Unlocked();

	UFUNCTION(Exec)
	void HopHopMode();
	
	UFUNCTION(Exec)
	void TestMode();
	virtual void ResetTestModes() override;

	UFUNCTION(Exec)
	void ShiftToPartTwo();

	UFUNCTION(Exec)
	void TestSecretSlogan(FString SloganToTest);
	
	UFUNCTION(Exec)
	void AddExtraLevels();

	UFUNCTION(Exec)
	void ShowHideUI(bool Show);

	EPlayMode TempPlayMode;

	// Inherited via IGameInstanceAccessoryInterface
	virtual void SetLastLevelName() override;
	virtual FCurrentProgress GetCurrentProgress() const override;
	virtual FName GetLevelName(int32 CurrentLevel, int32 CurrentDungeon) override;
	virtual FPlayModeInformation GetPlayModeInformation(EPlayMode PlayMode) const override;
	virtual FPlayModeModifierInformation GetPlayModeModifierInformation(EPlayMode PlayMode) const override;
	virtual EPlayMode GetPlayMode() const override;
	virtual int32 GetNumberToSpawn(ESpawnPointType SpawnPointType, EPartInformation CurrentPart) override;
	virtual float GetTimeToGetHungry(EPartInformation CurrentPart) override;
	virtual FCharacterSetup GetCharacterSetup() const override;
	virtual FSpiderSetup GetSpiderSetup() const override;
	virtual FClockSetup GetClockSetup() const override;
	virtual bool ShouldWaitForEndOfTime() const override;
	UFUNCTION(BlueprintCallable)
	virtual bool ConsoleInfoShown() const override;
	UFUNCTION(BlueprintCallable)
	virtual void SetConsoleInfoShown(bool InfoShown) override;
	virtual void SetNoiseMultiplier(float Value) override;
	virtual int32 CalculateCurrentDifficulty() override;
	virtual void CountBeforeBackToMenu() override;
	virtual void SetCurrentDifficulty(int32 Difficulty) override;
	virtual bool IsPart2() const override;
	virtual bool HasTutorialFinished() const override;
	virtual bool HasPartAchieved(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) const override;
	virtual int32 CalculateCurrentDifficultyForPart(int32 Level, int32 Dungeon, int32 Part) override;
	virtual int32 GetMaxDifficulties(int32 Level, int32 Dungeon) const override;
	virtual int32 GetSpiderPathNumber(EPartInformation CurrentPart) const override;
	virtual TArray<float> GetSpiderPathSpreadValues(EPartInformation CurrentPart) const override;


	// Inherited via IGameInstanceUIInterface
	virtual void ShowUIEntryMessageInformation() override;
	virtual TArray<FSecretCredential> GetCredentials() const override;
	virtual TArray<int32> GetKnownSecretSloganIndices() const override;
	virtual void ShowUITutorialInformation(FText Title, FText Message, int32 index) override;
	virtual void SetUIActive(bool IsActive) override;
	virtual void SetMapActive(bool IsActive) override;
		
	// Geerbt über IGameInstanceInterface
	virtual void CheckSecretMessageTypedIn(const FText& Text) override;
	virtual void UpdateGameStateValues() override;
	virtual void ResetPlayModes() override;
	virtual void TestExtraLevelsSetup() override;

	// Geerbt über IGameInstanceMenuInterface
	virtual void ShowNewCredentials() override;
	virtual void OpenMenuMap() override;
	virtual void HideUnwantedUIElementsOnFinish() override;
	virtual void ContinueForced() override;
	virtual void TutorialFinished() override;

	TArray<FSecretConnection> SecretConnections;

	FTimerHandle TimerHandle_ReloadMenu;

	void AddExtraLevelGameInformation();
	void AddExtraLevelPlayModeInformation();
	void AddExtraLevelAchievementInformation();

private:
	bool bAlreadyAddedExtraLevels;

	// Inherited via IGameInstanceAccessoryInterface
	virtual TArray<TArray<TArray<FSecretCredential>>> GetKnownSecretCredentialsByArrays(int32 CurrentLevel) const override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual TArray<int32> GetSolvedSloganIndices() const override;

	virtual TArray<int32> GetCurrentSolvedSloganIndices() const override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual TArray<FString> GetSecretSlogans() const override;
	virtual bool CompetitionAvailable() const override;
	virtual int32 GetCurrentHeatPoints() const override;
	virtual EPlayMode GetCurrentPreferredPlayMode() const override;
	virtual bool IsCompeteAccessible() const override;
	virtual class UCurrentScoreUserWidget* AddScoreWidget() override;
	void CheckHighScores();
	void ReadInHighScores();
	// Inherited via IGameInstanceAccessoryInterface
	virtual EPlayPath GetCurrentPlayPath() const override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual void SetScoreInGame(int32 ScoreInGame) override;
	virtual void SetMeatBonus(int32 MeatBonus) override;
	virtual void SetHungerBonus(int32 HungerBonus) override;
	virtual void SetFinishBonus(int32 FinishBonus) override;
	virtual void SetPickupBonus(int32 PickupBonus) override;
	virtual void SetFinalScore(int32 FinalScore) override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual void ShowFinalScore() override;

	// Inherited via IGameInstanceMenuInterface
	virtual void HideFinalScore() override;

	// Geerbt über IGameInstanceAccessoryInterface
	virtual TArray<int32> GetSlogansIndicesLevelpoints() const override;

	// Geerbt über IGameInstanceUIInterface
	virtual void ShowPickupWidget(bool Show) override;

	// Geerbt über IGameInstanceAccessoryInterface
	virtual TArray<float> GetFinalMonsterHungerAverages() const override;

	// Inherited via IGameInstanceMenuInterface
	virtual void HideWinInformation() override;

	// Inherited via IGameInstanceUIInterface
	virtual void CallHideHighscore() override;

	// Inherited via IGameInstanceUIInterface
	virtual void CallShowHighscore() override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual bool IsNewHighScoreAchieved(const int32 Level, const int32 Dungeon, const int32 Difficulty, const int32 Part, const int32 Score, const float Time) override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual TArray<FHighScoreEntry> GetHighScoresForSettings(EPlayMode PlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part) override;
	
	virtual void AddHighScoreEntry(FString Name) override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual void PickupCollected(TSubclassOf<class APowerUp>) override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual void PickupDropped(FVector Location) override;

	// Geerbt über IGameInstanceAccessoryInterface
	virtual bool HasPickupSpawnLocation(FName PickupName) const override;

	// Geerbt über IGameInstanceAccessoryInterface
	virtual FVector GetSpawnLocation(FName PickupName) const override;
	virtual void SetSpawnLocation(FName PickupName, FVector SpawnLocation) override;

	// Inherited via IGameInstanceUIInterface
	virtual void SetTrapBarValue(float Value) override;
	virtual void ResetTrapBar() override;
	virtual void ShowTrapBar() override;

	// Inherited via IGameInstanceInterface
	virtual void TestCompetitionMode() override;

	// Inherited via IGameInstanceAccessoryInterface
	virtual bool IsPowerUpAvailable(TSubclassOf<class APowerUp> PowerUp) const override;

	// Inherited via IGameInstanceMenuInterface
	virtual bool IsCaretakerOne() const override;
};
