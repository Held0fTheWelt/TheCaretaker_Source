/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Chest/ChestActor.h"

#include "TimerManager.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Game/CaretakerGameState.h"
#include "States/Player/CaretakerPlayerState.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

#pragma region Constructor
AChestActor::AChestActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	if (!ChestRoot)
		ChestRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ChestRoot"));
	if (!ChestMesh)
		ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestComponent"));
	if (!CoverMesh)
		CoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoverMeshComponent"));
	if (!GoldCoverMesh)
		GoldCoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoldCoverMeshComponent"));
	if (!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolumeComponent"));
	
	RootComponent = ChestRoot;

	ChestMesh->SetupAttachment(RootComponent);


	CoverMesh->SetupAttachment(ChestMesh);
	CoverMesh->SetRelativeLocation(FVector(0.f, -25.f, 30.f));

	GoldCoverMesh->SetupAttachment(ChestMesh);

	// This is a query only trigger volume
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetBoxExtent(FVector(40.f, 40.f, 50.f));
	TriggerVolume->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	TriggerVolume->SetupAttachment(RootComponent);

	RotationAxis = ERotationAxis::RA_X;

	Delay = 1.0f;
	AngleWhenOpen = -90.f;

	bIsClosed = false;
	MarkerWidget = nullptr;
}
#pragma endregion

#pragma region Begin Play
void AChestActor::BeginPlay()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	Super::BeginPlay();
	
	if (bIsClosed)
	{		
		FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
		CoverMesh->SetRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
	else
	{
		FRotator NewRotation = FRotator();
		switch (RotationAxis)
		{
		case ERotationAxis::RA_NONE:
			break;
		case ERotationAxis::RA_X:
			NewRotation = FRotator( AngleWhenOpen, 0, 0);
			break;
		case ERotationAxis::RA_Y:
			NewRotation = FRotator( 0, AngleWhenOpen, 0);
			break;
		case ERotationAxis::RA_Z:
			NewRotation = FRotator( 0, 0, AngleWhenOpen);
			break;
		default:
			break;
		}
		CoverMesh->SetRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
	
	if (FloatCurve != NULL)
	{
		AnimationTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		AnimationTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(AnimationTimeline); // Add to array so it gets saved
		AnimationTimeline->SetNetAddressable();	// This component has a stable name that can be referenced for replication

		AnimationTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		AnimationTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		AnimationTimeline->SetLooping(false);
		AnimationTimeline->SetTimelineLength(5.0f);
		AnimationTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		AnimationTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		AnimationTimeline->AddInterpFloat(FloatCurve, onTimelineCallback, FName("AngleValue"));
		AnimationTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		AnimationTimeline->RegisterComponent();
	}


	TArray<AActor*>Actors;
	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerGameState::StaticClass(), Actors);
	for (const auto& Actor : Actors) {

		ACaretakerGameState* GameStateActor = Cast<ACaretakerGameState>(Actor);
		if (GameStateActor != nullptr)
		{
			ChestIsSolved.AddDynamic(GameStateActor, &ACaretakerGameState::CountDownChests);
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerPlayerState::StaticClass(), Actors);
	for (const auto& Actor : Actors) {

		ACaretakerPlayerState* PlayerStateActor = Cast<ACaretakerPlayerState>(Actor);
		if (PlayerStateActor != nullptr)
		{
			CurrentPlayerState = PlayerStateActor;
		}
	}

	if (TriggerVolume != nullptr)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AChestActor::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AChestActor::OnOverlapEnd);
	}
	else
	{
		LOG_WARNING(InitializationLog, "TriggerVolume was null ! This shouldn't happen!")
	}

	RegisterMarkerWidget(true);
}
#pragma endregion

#pragma region Left MouseButton Clicked
void AChestActor::RegisterMarkerWidget(bool Register)
{
	if (Register)
	{

		IGameInstanceUIInterface* GameInstance = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameInstance was null !")
				return;
		}

		MarkerWidget = GameInstance->AttachActorMarkerWidget(this, MapMarkerTexture, false);
		LOG_DISPLAY(InitializationLog, "Marker Widget setup okay!");
	}
	else
	{
		TArray<UUserWidget*> Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UMiniMapInterface::StaticClass(), false);
		if (Widgets.Num() == 0)
		{
			LOG_WARNING(RuntimeExecutionLog, "Widget Array was length 0. No MiniMap found. This shouldn't happen !")
		}
		else
		{
			for (auto Widget : Widgets)
			{
				IMiniMapInterface* MiniMap = Cast<IMiniMapInterface>(Widget);
				if (MiniMap == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "Could not cast Actor to MiniMap. This shouldn't happen !")
				}
				else
				{
					MiniMap->UnregisterWidgetInterface(MarkerWidget);
					MarkerWidget->UnregisterActorMarkerWidget();
					MarkerWidget->RemoveFromParent();
				}
			}
		}
	}
}
void AChestActor::LeftMouseButtonClicked(ICollectableInterface* &CollectableRef)
{
	if (!bBlockInteraction)
	{
		CloseChest();		
	}
}
#pragma endregion

#pragma region TimerHandle Finished
void AChestActor::TimerHandleFinished()
{

	PlayTimeline();
	Closing();
}
#pragma endregion

#pragma region Close Chest
void AChestActor::CloseChest()
{
	if (bIsClosed) return;


	if (CurrentPlayerState == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not close chest, because PlayerState pointer was null!!");

		return;
	}
	if (CurrentPlayerState->GetGoldCount() > 0)
	{
		bBlockInteraction = true;
		CurrentPlayerState->RemoveGold(1);	

		Interacted();
		GoldCoverMesh->SetVisibility(true);
		TriggerVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (ChestIsSolved.IsBound())
		{
			ChestIsSolved.Broadcast(Part);
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "Cannot count CloseChest, because it is unbound !!");
		}
		GetWorldTimerManager().SetTimer(ChestTimerHandle, this, &AChestActor::TimerHandleFinished, Delay);

		if (InteractingSound != nullptr)
		{
			UGameplayStatics::SpawnSoundAttached(InteractingSound, GoldCoverMesh);
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "Cannot play sound to CloseChest, because it is null! Check your blueprint setup!");

		}
	}
}
#pragma endregion

#pragma region Timeline Component
void AChestActor::TimelineCallback(float interpolatedVal)
{
	// Calculate the new doors rotation
	FRotator NewRotation = FRotator();
	switch (RotationAxis)
	{
	case ERotationAxis::RA_NONE:
		break;
	case ERotationAxis::RA_X:
		NewRotation = FRotator(interpolatedVal * AngleWhenOpen, 0, 0);
		break;
	case ERotationAxis::RA_Y:
		NewRotation = FRotator(0, interpolatedVal * AngleWhenOpen, 0);
		break;
	case ERotationAxis::RA_Z:
		NewRotation = FRotator(0, 0, interpolatedVal * AngleWhenOpen);
		break;
	default:
		break;
	}
	// Set new rotation to mesh
	CoverMesh->SetRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
}

void AChestActor::TimelineFinishedCallback()
{
	bIsClosed = true;
	Closed();

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

	AchievementInstance->CountAchievement(EAchievementType::AT_GOLD);

	RegisterMarkerWidget(false);
}

// Plays the Timeline from the beginning
void AChestActor::PlayTimeline()
{
	if (AnimationTimeline != NULL)
	{
		AnimationTimeline->ReverseFromEnd();
		//DoorTimeline->PlayFromStart();
	}
}
#pragma endregion

#pragma region Collision Volume
#pragma region On Overlap Begin
void AChestActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	if (OtherActor != Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		return;
	}

	if (bIsClosed)
	{
		return;
	}
	
	ChestMesh->SetCustomDepthStencilValue(2);
	CoverMesh->SetCustomDepthStencilValue(2);

	ChestMesh->SetRenderCustomDepth(true);
	CoverMesh->SetRenderCustomDepth(true);
}
#pragma endregion

#pragma region On Overlap End
void AChestActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	if (bIsClosed)
	{
		return;
	}

	ChestMesh->SetCustomDepthStencilValue(0);
	CoverMesh->SetCustomDepthStencilValue(0);

	ChestMesh->SetRenderCustomDepth(false);
	CoverMesh->SetRenderCustomDepth(false);
}
#pragma endregion
#pragma endregion
void AChestActor::SetMarkerWidget(UActorMarkerWidget* NewMarkerWidget)
{
	MarkerWidget = NewMarkerWidget;
}