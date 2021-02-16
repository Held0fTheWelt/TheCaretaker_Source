/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Trap/TrapActor.h"

#include "TimerManager.h"
#include "FMODAudioComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Game/CaretakerGameState.h"
#include "States/Player/CaretakerPlayerState.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Structs/FMOD/FMODParameterSetList.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#pragma region Constructor
ATrapActor::ATrapActor()
{ 	
	PrimaryActorTick.bCanEverTick = true;

	if (!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolumeComponent"));
	if (!BaseMesh)
		BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	if (!TrapMesh)
		TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMeshComponent"));
	if(!AudioComponent)
		AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	RootComponent = TriggerVolume;

#pragma region TriggerVolume
	// This is a query only trigger volume
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetBoxExtent(FVector(80.f, 80.f, 50.f));
#pragma endregion

	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));

	TrapMesh->SetupAttachment(BaseMesh);
	AudioComponent->SetupAttachment(BaseMesh);
	HeightWhenArmed = 90.f;
	FMODParameterName = EName::NAME_None;

	bIsArmed = false;

	MarkerWidget = nullptr;
	UIInstance = nullptr;
}
#pragma endregion

#pragma region Begin Play
void ATrapActor::BeginPlay()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	Super::BeginPlay();

	UCurveFloat* CurrentCurve = nullptr;

	if (bIsArmed)
	{		
		TrapMesh->SetRelativeLocation(FVector(0.f,0.f,HeightWhenArmed), false, 0, ETeleportType::None);
		CurrentCurve = TrapSnapCurve;
	}
	else
	{
		TrapMesh->SetRelativeLocation(FVector(0), false, 0, ETeleportType::None);
		CurrentCurve = TrapAimCurve;
	}

	if (CurrentCurve != NULL)
	{
		InitTimeline(CurrentCurve);
	}


	if (AudioComponent == nullptr)
	{
		LOG_WARNING(InitializationLog, "AudioComponent not found! This shouldn't happen !")
	}
	else
	{
		if (BeginInteractSound != nullptr)
		{
			AudioComponent->SetSound(BeginInteractSound);
		}
		else
		{
			LOG_WARNING(InitializationLog, "Cannot set sound to begin arming Trap , because it is null! Check your blueprint setup!");
		}
	}

	TArray<AActor*>Actors;
	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerGameState::StaticClass(), Actors);
	for (const auto& Actor : Actors) {

		ACaretakerGameState* GameStateActor = Cast<ACaretakerGameState>(Actor);
		if (GameStateActor != nullptr)
		{
			TrapIsSolved.AddDynamic(GameStateActor, &ACaretakerGameState::CountDownTraps);
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
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrapActor::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATrapActor::OnOverlapEnd);
	}
	else
	{
		LOG_WARNING(InitializationLog, "TriggerVolume was null ! This shouldn't happen!")
	}

	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance. This shouldn't happen!")
			return;
	}

	FMODParameterSet ParameterSet = GameInstance->GetFMODParameterSet(EFMODParameterType::FMOD_PT_TRAP);

	FMODParameterName = ParameterSet.ParameterName;

	UIInstance = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (UIInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
		return;
	}

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());

	if (GameMode == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameMode. This shouldn't happen!")
		return;
	}

	IGameModeInterface* DungeonGameMode = Cast<IGameModeInterface>(GameMode);

	if (DungeonGameMode == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast GameMode to TheCaretakerDungeon GameMode. Is the GameMode setup correctly ?")
		return;
	}

	FMODAudio = DungeonGameMode->GetFMODComponent();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	RegisterMarkerWidget(true);
}
#pragma endregion

#pragma region Left MouseButton Clicked
void ATrapActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (!bBlockInteraction && bCanArmTrap)
	{
		ArmTrap();

		if (UIInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
			return;
		}
		else
		{
			UIInstance->ShowTrapBar();
		}
	}
}
#pragma endregion

void ATrapActor::TrapSolved()
{
	Armed();
}

#pragma region TimerHandle Finished
void ATrapActor::TimerHandleFinished()
{
	PlayTimeline();

	if (bIsArmed)
	{
		
	}
	else
	{
		
	}
}
#pragma endregion

#pragma region Close Chest
void ATrapActor::ArmTrap()
{
	if (bIsArmed) return;

	bBlockInteraction = true;

	TimerHandleFinished();

	if (AudioComponent == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "AudioComponent was null ! This shouldn't happen !")
	}
	else
	{
		if (AudioComponent->Sound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "AudioComponent had no Sound attached !")
		}
		else
		{
			AudioComponent->Play();
		}
	}

	if (InteractingSound != nullptr)
	{
		AudioComponent->SetSound(InteractingSound);
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot set sound to play arming Trap , because it is null! Check your blueprint setup!");

	}	

	FMODAudio->SetParameter(FMODParameterName, 1.f);
}
#pragma endregion

#pragma region Timeline Component
void ATrapActor::TimelineCallback(float interpolatedVal)
{		
	if (bIsArmed)
	{
		TrapMesh->SetRelativeLocation(FVector(0.f,0.f, interpolatedVal), false, 0, ETeleportType::None);
		
		if (HeightWhenArmed < 0)
		{
			if (interpolatedVal <= HeightWhenArmed)
			{
				AnimationTimeline->Stop();
				bIsArmed = false;
			}
		}
		else
		{
			if (interpolatedVal <= 0)
			{
				AnimationTimeline->Stop();
				bIsArmed = false;
			}
		}
	}
	else
	{
		if (PlayerController == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not find PlayerController ! This shouldn't happen !")
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("%f"), PlayerController->GetInputKeyTimeDown(EKeys::LeftMouseButton));

			if (PlayerController->GetInputKeyTimeDown(EKeys::LeftMouseButton) <= 0 || bCanArmTrap == false)
			{
				PlaySnapSound();
				FMODAudio->SetParameter(FMODParameterName, 0.f);
				TrapMesh->SetRelativeLocation(FVector(0), false, 0, ETeleportType::None);
				AnimationTimeline->Stop();
				bBlockInteraction = false;
				if (UIInstance == nullptr)
				{
					LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
						return;
				}
				else
				{
					UIInstance->ResetTrapBar();
				}
				return;
			}
		}


		TrapMesh->SetRelativeLocation(FVector(0.f,0.f, interpolatedVal), false, 0, ETeleportType::None);

		if (HeightWhenArmed < 0)
		{
			if (interpolatedVal <= HeightWhenArmed)
			{

				if (UIInstance == nullptr)
				{
					LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
						return;
				}
				else
				{
					UIInstance->ResetTrapBar();
				}
				bIsArmed = true;
				AnimationTimeline->Stop();
				TrapSolved();
			}
			else
			{
				if (UIInstance == nullptr)
				{
					LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
						return;
				}
				else
				{
					UIInstance->SetTrapBarValue(FMath::Abs(interpolatedVal / HeightWhenArmed));
				}
				if (AudioComponent == nullptr)
				{
					LOG_WARNING(RuntimeLog, "AudioComponent was null ! This shouldn't happen !")
				}
				else
				{
					if (!AudioComponent->IsPlaying())
					{
						AudioComponent->Play();
					}
				}
			}
		}
		else
		{
			if (interpolatedVal >= HeightWhenArmed)
			{
				if (UIInstance == nullptr)
				{
					LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
						return;
				}
				else
				{
					UIInstance->ResetTrapBar();
				}
				bIsArmed = true;
				AnimationTimeline->Stop();
				TrapSolved();
			}
			else
			{
				if (AudioComponent == nullptr)
				{
					LOG_WARNING(RuntimeLog, "AudioComponent was null ! This shouldn't happen !")
				}
				else
				{
					if (!AudioComponent->IsPlaying())
					{
						AudioComponent->Play();
					}
				}
				if (UIInstance == nullptr)
				{
					LOG_WARNING(InitializationLog, "Couldn't find GameInstance ! This shouldn't happen !")
						return;
				}
				else
				{
					UIInstance->SetTrapBarValue(FMath::Abs(interpolatedVal / HeightWhenArmed));
				}
			}
		}

	}
}

void ATrapActor::TimelineFinishedCallback()
{
	ArmingTrap();

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

	AchievementInstance->CountAchievement(EAchievementType::AT_TRAP);

	FMODAudio->SetParameter(FMODParameterName, 0.f);

	if (TrapIsSolved.IsBound())
	{
		TrapIsSolved.Broadcast();
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot count Trap, because it is unbound !!");
	}

	RegisterMarkerWidget(false);
}

// Plays the Timeline from the beginning
void ATrapActor::PlayTimeline()
{
	if (AnimationTimeline != NULL)
	{
		AnimationTimeline->PlayFromStart();
	}
}
#pragma endregion

#pragma region Collision Volume
#pragma region On Overlap Begin
void ATrapActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	BaseMesh->SetCustomDepthStencilValue(2);
	TrapMesh->SetCustomDepthStencilValue(2);

	BaseMesh->SetRenderCustomDepth(true);
	TrapMesh->SetRenderCustomDepth(true);

	if (bIsArmed)
	{
		PlaySnapSound();

		IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (Menu == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
		}
		else
		{
			Menu->OpenIngameMenu(EIngameMenuCall::IMC_DEATHBYTRAP);
		}

		IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (AchievementInstance == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
				return;
		}

		AchievementInstance->CountAchievement(EAchievementType::AT_DEATHBYTRAP);

		InitTimeline(TrapSnapCurve);

		TimerHandleFinished();

		return;
	}

	bCanArmTrap = true;
}
void ATrapActor::PlaySnapSound()
{
	if (TrapSnapSound == nullptr)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "No Snap Sound in Bluepring")
	}
	else
	{
		AudioComponent->SetSound(TrapSnapSound);
		AudioComponent->Play();
	}
}
void ATrapActor::InitTimeline(UCurveFloat* CurrentCurve)
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

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
	AnimationTimeline->AddInterpFloat(CurrentCurve, onTimelineCallback, FName("HeightValue"));
	AnimationTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);
	AnimationTimeline->RegisterComponent();
}
#pragma endregion

#pragma region On Overlap End
void ATrapActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	BaseMesh->SetCustomDepthStencilValue(0);
	TrapMesh->SetCustomDepthStencilValue(0);

	BaseMesh->SetRenderCustomDepth(false);
	TrapMesh->SetRenderCustomDepth(false);

	if (bIsArmed)
	{
		return;
	}

	bCanArmTrap = false;

}
void ATrapActor::RegisterMarkerWidget(bool Register)
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
#pragma endregion
#pragma endregion
void ATrapActor::SetMarkerWidget(UActorMarkerWidget* NewMarkerWidget)
{
	MarkerWidget = NewMarkerWidget;
}