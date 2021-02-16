/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Monsters/MonsterFeedingVolumeActor.h"

#include "TimerManager.h"

#include "Pawns/Monster/MonsterPawn.h"
#include "Actors/Game/GameActor.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Structs/Anger/MonsterAnger.h"
#include "States/Game/CaretakerGameState.h"
#include "States/Player/CaretakerPlayerState.h"
#include "Widgets/Monsters/MonsterInformationWidget.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

#pragma region Constructor
AMonsterFeedingVolumeActor::AMonsterFeedingVolumeActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	if (!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolumeComponent"));
	
#pragma region TriggerVolume
	// This is a query only trigger volume
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetBoxExtent(FVector(80.f, 80.f, 100.f));

	TriggerVolume->SetupAttachment(RootComponent);
#pragma endregion

	TriggerVolume->SetupAttachment(RootComponent);

	if (AudioComponent == nullptr)
		AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("AudioComponent"));

	AudioComponent->SetupAttachment(RootComponent);

	TimeToGetHungry = 300;
	TimeInSecondsWhenFed = 10;
	MonsterName = EName::NAME_None;
	FoodToRemoveFromPlayer = 1;

	ConnectedMonsterCharacter = nullptr;

	ValuesToShout.Add(.33f);
	ValuesToShout.Add(.5f);
	ValuesToShout.Add(.66f);
	ValuesToShout.Add(.75f);

	bTutorialMode = false;

	NoisyModifier = 2.5f;

	HungerValueHistory = TArray<float>();

	TimeToCheckAverages = 5.f;
	NumberToAverage = 500;
	HungerValuesList = TArray<float>();

	bCompetitionMode = false;
}
#pragma endregion

#pragma region Begin Play
void AMonsterFeedingVolumeActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>Actors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerPlayerState::StaticClass(), Actors);
	for (const auto& Actor : Actors) {

		ACaretakerPlayerState* PlayerStateActor = Cast<ACaretakerPlayerState>(Actor);
		if (PlayerStateActor != nullptr)
		{
			CurrentPlayerState = PlayerStateActor;
		}
	}

	if (!TriggerVolume)
	{
		LOG_WARNING(InitializationLog, "TriggerVolume not found.\nThis shouldn't happen!");
		return;
	}
	else
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMonsterFeedingVolumeActor::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMonsterFeedingVolumeActor::OnOverlapEnd);
	}

	if (ConnectedMonsterCharacter != nullptr)
	{
		ConnectedMonsterCharacter->SetConnectedVolume(this);
	}

	ITutorialInterface* TutorialInterface = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (TutorialInterface == nullptr)
	{
		GameInstanceAccessory = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstanceAccessory == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
		}
		else
		{
			TimeToGetHungry = GameInstanceAccessory->GetTimeToGetHungry(Part);
		}

		SendAngryMessage = -1;

		LOG_DISPLAY(InitializationLog, "Begin Play Feeding Widget OK")
	}
	else
	{
		bTutorialMode = true;
	}

	if (!bTutorialMode)
	{
		Actors.Empty();
		// Pick only Actors with Interface, instead of iterating whole World:
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerGameState::StaticClass(), Actors);
		for (const auto& Actor : Actors) {

			ACaretakerGameState* GameStateActor = Cast<ACaretakerGameState>(Actor);
			if (GameStateActor != nullptr)
			{
				MonsterStatus.AddDynamic(GameStateActor, &ACaretakerGameState::MonsterReport);
			}
		}
	}

	if (GameInstanceAccessory != nullptr)
	{
		if (GameInstanceAccessory->IsCompeteAccessible())
		{
			bCompetitionMode = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AverageTimer, this, &AMonsterFeedingVolumeActor::CheckAverageValues, TimeToCheckAverages, true);
		}
	}
}
void AMonsterFeedingVolumeActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bGameIsStarted && !bPaused)
	{
		GetHungry(DeltaSeconds);
	}
	else
	{

	}
}
#pragma endregion

#pragma region Left MouseButton Clicked
void AMonsterFeedingVolumeActor::LeftMouseButtonClicked(ICollectableInterface* &CollectableRef)
{
	FeedMonster();
}
#pragma endregion

//AMonsterFeedingVolumeActor::~AMonsterFeedingVolumeActor()
//{
//	if (GetWorld()->GetTimerManager().TimerExists(TimerHandle_AverageTimer))
//	{
//		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AverageTimer);
//	}
//}

#pragma region Initialization Complete
void AMonsterFeedingVolumeActor::InitializationComplete()
{
	if (FeedingUIWidget == nullptr)
	{
		LOG_WARNING(InitializationLog, "Feeding Widget should be ready but isn't !!");
	}
	else
	{
		LOG_DISPLAY(InitializationLog, "Feeding Widget setup okay!");
		FeedingUIWidget->SetProgressBarPercentage(0.f);
		FeedingUIWidget->SetMonsterImage(MonsterImage);
		FeedingUIWidget->SetMonsterName(FText::FromName(MonsterName));
	}	

	IGameInstanceUIInterface* GameInstance = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance was null !")
		return;
	}

	MarkerWidget = GameInstance->AttachActorMarkerWidget(ConnectedMonsterCharacter, MonsterImage, true);
	LOG_DISPLAY(InitializationLog, "Marker Widget setup okay!");
}
#pragma endregion

#pragma region Stop Game
void AMonsterFeedingVolumeActor::StopGame()
{
	Super::StopGame();

	bGameIsStarted = false;
}
#pragma endregion

#pragma region New Game
void AMonsterFeedingVolumeActor::NewGame()
{
	Super::NewGame();

	bGameIsStarted = true;
}

#pragma endregion

#pragma region Monster Fed
void AMonsterFeedingVolumeActor::MonsterFed()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not get GameInstance. This shouldn't happen!")
			return;
	}

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(GameInstance);
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
			return;
	}

	AchievementInstance->CountAchievement(EAchievementType::AT_MEAT);
}
const float AMonsterFeedingVolumeActor::CalculateFinalAverageHunger() 
{
	float Average = 0.f;

	for (int32 i = 0; i < HungerValueHistory.Num(); i++)
	{
		Average += HungerValueHistory[i];
	}

	Average += CalculateLastAverage();

	Average /= (HungerValueHistory.Num() + 1);

	return Average;
}
#pragma endregion

#pragma region Get Hungry
void AMonsterFeedingVolumeActor::GetHungry(float DeltaSeconds)
{
	if (GameInstanceAccessory == nullptr)
	{
//		LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
	}
	else
	{
		if (GameInstanceAccessory->GetPlayMode() == EPlayMode::PM_HOPHOP)
		{
			return;
		}
	}

	if (bPaused == true || bTutorialMode == true )
	{
//		LOG_WARNING(RuntimeLog, "Game is paused - not getting hungry")
		if (FeedingUIWidget != nullptr)
		{
			FeedingUIWidget->SetProgressBarPercentage(CurrentHungerTime / TimeToGetHungry);
		}

		return;
	}

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		LOG_WARNING(RuntimeLog, "World was null during Monster getting Hungry! This shouldn't happen !");
		return;
	}
	LastCurrentHungerTime = CurrentHungerTime;

	if (bIsNoisy)
	{
		CurrentHungerTime += DeltaSeconds * NoisyModifier;
	}
	else
	{
		CurrentHungerTime += DeltaSeconds;
	}
	//TArray<FStringFormatArg> args;
	//args.Add(FStringFormatArg(CurrentHungerTime));
	//FString Message = FString::Format(TEXT("Current Hunger Time : {0} "), args);
	//
	//LOG_VERBOSE(RuntimeLog , Message);
	int testHunger = TimeToGetHungry / 3;

	CheckIfAngry(0);

	if (CurrentHungerTime >= TimeToGetHungry)
	{
		CurrentHungerTime = TimeToGetHungry;
		if (MonsterAlarm.IsBound())
		{
			if (MarkerWidget != nullptr)
			{
				MarkerWidget->SetIsAngry(true);
			}
			else
			{
				LOG_WARNING(RuntimeLog, "Could not find Monster Marker Widget ! This shouldn't happen !")
			}
			MonsterAlarm.Broadcast(1.f);
		}
		else
		{
			LOG_WARNING(RuntimeLog, "Cannot broadcast MonsterAlarm to FMOD, because it is unbound")
		}
	}
	else {
		if (MarkerWidget != nullptr)
		{
			if (MarkerWidget->IsAngry())
			{
				MarkerWidget->SetIsAngry(false);
			}
		}
		else
		{
			LOG_WARNING(RuntimeLog, "Could not find Monster Marker Widget ! This shouldn't happen !")
		}		
	}

	if (FeedingUIWidget != nullptr)
	{
		FeedingUIWidget->SetProgressBarPercentage(CurrentHungerTime / TimeToGetHungry);
	}
	else
	{
		LOG_WARNING(RuntimeLog, "FeedingWidget was null during Monster getting Hungry! This shouldn't happen !");
	}

	if (MonsterStatus.IsBound())
	{
		FMonsterAnger ThisAnger;
		ThisAnger.Anger = CurrentHungerTime / TimeToGetHungry;
		ThisAnger.MonsterName = MonsterName;
		MonsterStatus.Broadcast(ThisAnger);
	}
	else
	{
		LOG_WARNING(RuntimeLog, "Cannot count CloseChest, because it is unbound !!");
	}

	if (bCompetitionMode == true)
	{
		//LOG_WARNING(RuntimeExecutionLog, "Competing")
		HungerValuesList.Add(CurrentHungerTime / TimeToGetHungry);
	}
}
#pragma endregion

#pragma region Feed Monster
void AMonsterFeedingVolumeActor::FeedMonster()
{
	if (CurrentPlayerState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not feed monster, because PlayerState pointer was null!!");
		return;
	}

	if (CurrentHungerTime < TimeInSecondsWhenFed)
	{
		return;
	}

	if (CurrentPlayerState->GetFoodCount() > 0)
	{
		CurrentPlayerState->RemoveFood(FoodToRemoveFromPlayer);
		CurrentHungerTime -= TimeInSecondsWhenFed;
		CurrentHungerTime = FMath::Clamp(CurrentHungerTime, 0.f, TimeToGetHungry);
		
		AddResourceEvent();

		MonsterFed();
	}
} 
#pragma endregion

#pragma region Set Feeding UI Widget
void AMonsterFeedingVolumeActor::SetFeedingUIWidget(UMonsterInformationWidget* Widget)
{
	if (Widget == nullptr)
	{

		return;
	}
	FeedingUIWidget = Widget;	
}
#pragma endregion

void AMonsterFeedingVolumeActor::CheckAverageValues()
{
	//LOG_WARNING(RuntimeExecutionLog, "Checking Average")
	if (HungerValuesList.Num() > NumberToAverage)
	{
		//LOG_WARNING(RuntimeExecutionLog, "Making Average")
		float Average = 0.f;
		
		for (int32 i = 0; i < NumberToAverage; i++)
		{
			Average += HungerValuesList[i];
		}

		for (int32 i = NumberToAverage - 1; i >= 0; i--)
		{
			HungerValuesList.RemoveAt(i);
		}

		Average /= NumberToAverage;

		HungerValueHistory.Add(Average);

		UE_LOG(LogTemp, Warning, TEXT("History List has %d values"), HungerValueHistory.Num());
	}

	if (HungerValuesList.Num() > NumberToAverage)
	{
		CheckAverageValues();
	}
}

float AMonsterFeedingVolumeActor::CalculateLastAverage() 
{
	if (GetWorld()->GetTimerManager().TimerExists(TimerHandle_AverageTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AverageTimer);
	}

	float Average = 0.f;

	for (int32 i = 0; i < HungerValuesList.Num(); i++)
	{
		Average += HungerValuesList[i];
	}

	Average /= HungerValuesList.Num();

	HungerValuesList.Empty();

	return Average;
}

#pragma region Set Game Paused
void AMonsterFeedingVolumeActor::SetGamePaused(bool SetGamePaused)
{
	bPaused = SetGamePaused;

	if (bPaused)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Pausing Game")
	
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Unpausing Game")
	}
}
#pragma endregion

#pragma region IsPaused
bool AMonsterFeedingVolumeActor::IsPaused() const
{
	return bPaused;
}
#pragma endregion

#pragma region Check If Angry
void AMonsterFeedingVolumeActor::CheckIfAngry(int8 Count)
{
	if (bPaused)
	{
		return;
	}

	if (ValuesToShout.Num() > Count)
	{
		if (CurrentHungerTime / TimeToGetHungry > ValuesToShout[Count])
		{
			CheckIfAngry(Count + 1);
			return;
		}
		else
		{
			if (SendAngryMessage < Count - 1)
			{
				AudioComponent->SetSound(MonsterRoarSound);
				AudioComponent->Play();

//				UGameplayStatics::SpawnSound2D(GetWorld(), MonsterRoarSound);

				if (MarkerWidget != nullptr)
				{
					MarkerWidget->PlayWidgetAnimation(0);
				}
				else
				{
					LOG_WARNING(RuntimeLog, "Could not find Monster Marker Widget ! This shouldn't happen !")
				}
				if (Count - 1 == 0)
				{
					ConnectedMonsterCharacter->PlayHungryAnimation(true);
				}
			}
			SendAngryMessage = Count - 1;
			if (SendAngryMessage == -1)
			{
				ConnectedMonsterCharacter->PlayHungryAnimation(false);
			}
			return;
		}
	}
	else
	{
		if (SendAngryMessage < Count - 1)
		{
			AudioComponent->SetSound(MonsterRoarSound);
			AudioComponent->Play();

			//UGameplayStatics::SpawnSound2D(GetWorld(), MonsterRoarSound);

			//LOG_WARNING(RuntimeExecutionLog, "Spawning Roar Sound")
			if (MarkerWidget != nullptr)
			{
				MarkerWidget->PlayWidgetAnimation(0);
			}
			else
			{
				LOG_WARNING(RuntimeLog, "Could not find Monster Marker Widget ! This shouldn't happen !")
			}
		}
		MonsterAlarm.Broadcast(1.f - (1.f - (CurrentHungerTime / TimeToGetHungry))/ (1.f - ValuesToShout[Count - 1]));
		SendAngryMessage = Count - 1;		
	}
	if (SendAngryMessage == -1)
	{
		ConnectedMonsterCharacter->PlayHungryAnimation(false);
	}
}
#pragma endregion

#pragma region Instant Monster Hunger
void AMonsterFeedingVolumeActor::InstantMonsterHunger()
{
	CurrentHungerTime = TimeToGetHungry;
}
#pragma endregion

#pragma region Noisy Pickup
void AMonsterFeedingVolumeActor::NoisyPickup(bool IsNoisy)
{
	bIsNoisy = IsNoisy;
}

float AMonsterFeedingVolumeActor::GetAverageHunger() const
{
	if (HungerValueHistory.Num() == 0)
	{
		return 0.0f;
	}
	
	float ReturnValue = 0.f;

	// Wrong method
	//for (auto HungerValue : HungerValueHistory)
	//{
	//	ReturnValue += HungerValue;
	//}

	//ReturnValue /= HungerValueHistory.Num();
	
	return ReturnValue;
}
#pragma endregion

#pragma region TriggerVolume
void AMonsterFeedingVolumeActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	if (ConnectedMonsterCharacter == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not outline Monster, because value for connected monster character is null. Is it set in the level setup ?")
	}
	else
	{
		AMonsterPawn* Monster = Cast<AMonsterPawn>(ConnectedMonsterCharacter);

		if (Monster == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog,"Could not cast Monster to MonsterPawn! This shouldn't happen !")
		}
		else
		{
			USkeletalMeshComponent* Root = Monster->GetMesh();
			if (Root == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog,"Could not cast Pawn Root Component to SkeletalMesh for Outlining. This shouldn't happen !")
			}
			else
			{
				Root->SetRenderCustomDepth(true);
				Root->SetCustomDepthStencilValue(2);
			}
		}
	}
}

void AMonsterFeedingVolumeActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}
	if (ConnectedMonsterCharacter == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not outline Monster, because value for connected monster character is null. Is it set in the level setup ?")
	}
	else
	{
		AMonsterPawn* Monster = Cast<AMonsterPawn>(ConnectedMonsterCharacter);

		if (Monster == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast Monster to MonsterPawn! This shouldn't happen !")
		}
		else
		{
			USkeletalMeshComponent* Root = Monster->GetMesh();
			if (Root == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not cast Pawn Root Component to SkeletalMesh for Outlining. This shouldn't happen !")
			}
			else
			{
				Root->SetRenderCustomDepth(false);
				Root->SetCustomDepthStencilValue(0);
			}
		}
	}
}
#pragma endregion