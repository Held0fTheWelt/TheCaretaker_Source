/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Game/GameActor.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/Monsters/Feeding/MonsterFeedingInterface.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Structs/Anger/MonsterAnger.h"
#include "MonsterFeedingVolumeActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMonsterAlarm, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMonsterAngry, class USoundBase*, SoundBase );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMonsterStatus, FMonsterAnger, MonsterAnger);

UCLASS()
class THECARETAKER_API AMonsterFeedingVolumeActor : public AGameActor, public IMouseInteractionInterface, public IMonsterFeedingInterface, public IPauseGameInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterFeedingVolumeActor();

	//~AMonsterFeedingVolumeActor();
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UMonsterInformationWidget* FeedingUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outlining")
	class AMonsterPawn* ConnectedMonsterCharacter;


	void InitializationComplete();

	virtual void StopGame() override;
	virtual void NewGame() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Resource")
	void AddResourceEvent();
	
	UPROPERTY()
	FMonsterAngry MonsterAngry;
	
	UPROPERTY()
	FMonsterAlarm MonsterAlarm;

	virtual void LeftMouseButtonClicked(class ICollectableInterface* &CollectableRef) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void MonsterFed();

	virtual const float CalculateFinalAverageHunger() override;
private:
	void GetHungry(float DeltaSeconds);

	UPROPERTY()
	TArray<float> HungerValueHistory;

	UPROPERTY()
	class UActorMarkerWidget* MarkerWidget;
	void FeedMonster();

	UPROPERTY(VisibleAnywhere, Category = "Pause")
	bool bPaused;

	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TArray<float> ValuesToShout;

	UPROPERTY(EditAnywhere, Category = "Monster")
	TEnumAsByte<EPartInformation> Part;

	UPROPERTY(EditAnywhere, Category = "Monster")
	FName MonsterName;
	
	UPROPERTY(EditAnywhere, Category = "Monster")
	float TimeToGetHungry;

	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	float TimeInSecondsWhenFed;

	UPROPERTY(VisibleAnywhere, Category = "GameMode")
	bool bTutorialMode;

	UPROPERTY(EditDefaultsOnly, Category = "Monster | Noisy")
	float NoisyModifier;

	FTimerHandle TimerHandle_AverageTimer;
public:
	UPROPERTY(VisibleAnywhere, Category = "Monster")
	float CurrentHungerTime;

	UPROPERTY(EditDefaultsOnly, Category = "Monster | Average")
	float TimeToCheckAverages;

	UPROPERTY(EditDefaultsOnly, Category = "Monster | Average")
	int32 NumberToAverage;

	UPROPERTY()
	TArray<float> HungerValuesList;

	UPROPERTY(EditAnywhere, Category = "Monster")
	int32 FoodToRemoveFromPlayer;

	UPROPERTY(EditAnywhere, Category = "Monster")
	class UTexture2D* MonsterImage;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Monster")
	class USoundBase* MonsterRoarSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Monster")
	class USoundBase* MonsterFeedSound;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Monster")
	class USoundBase* MonsterCalmSound;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Monster")
	class USoundBase* MonsterAngrySound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UAudioComponent* AudioComponent;

	FMonsterStatus MonsterStatus;
private:
	IGameInstanceAccessoryInterface* GameInstanceAccessory;

	virtual void SetFeedingUIWidget(UMonsterInformationWidget* Widget);

	float LastCurrentHungerTime;

	bool bCompetitionMode;

	UFUNCTION()
	void CheckAverageValues();

	float CalculateLastAverage() ;

	class ACaretakerPlayerState* CurrentPlayerState;

	//bool SendAngryAlreadyOnce;
	UPROPERTY(VisibleAnywhere, Category = "Monster")
	int8 SendAngryMessage;

	// Inherited via IPauseGameInterface
	virtual void SetGamePaused(bool SetGamePaused) override;
	virtual bool IsPaused() const;
	void CheckIfAngry(int8 Count);

	// Geerbt über IMonsterFeedingInterface
	virtual void InstantMonsterHunger() override;

	// Inherited via IMonsterFeedingInterface
	virtual void NoisyPickup(bool IsNoisy) override;

	bool bIsNoisy;

	// Inherited via IMonsterFeedingInterface
	virtual float GetAverageHunger() const override;
};
