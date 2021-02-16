/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Door/DoorActor.h"

#include "TimerManager.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Interfaces/DungeonMaster/DungeonMasterInterface.h"
#include "Curves/CurveFloat.h"
#include "Engine/World.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "UObject/ConstructorHelpers.h"


#pragma region Constructor
ADoorActor::ADoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!Pivot)
		Pivot = CreateDefaultSubobject<USceneComponent>(FName("Pivot"));
	if (!TriggerVolume1)
		TriggerVolume1 = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume1Component"));
	if (!TriggerVolume2)
		TriggerVolume2 = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume2Component"));
	if (!Mesh)
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorComponent"));

	RootComponent = Pivot;

	Mesh->SetupAttachment(RootComponent);

#pragma region TriggerVolume 1
	// This is a query only trigger volume
	TriggerVolume1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume1->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume1->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);	
	TriggerVolume1->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	

	TriggerVolume1->SetBoxExtent(FVector(80.f, 25.f, 100.f));
	TriggerVolume1->SetRelativeLocation(FVector(60.f, -25.f, 110.f));
	
	TriggerVolume1->SetupAttachment(RootComponent);
#pragma endregion

#pragma region TriggerVolume 2
	// This is a query only trigger volume
	TriggerVolume2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume2->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	TriggerVolume2->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume2->SetBoxExtent(FVector(80.f, 25.f, 100.f));
	TriggerVolume2->SetRelativeLocation(FVector(60.f, 25.f, 110.f));

	TriggerVolume2->SetupAttachment(RootComponent);
#pragma endregion

	Delay = 2.0f;

	MaxTurn = 90.0f;

	CurrentDirection = 0.f;

	bDoorIsUsable = true;

	DoorOpeningTriggerVolume1 = 1.0;
	DoorOpeningTriggerVolume2 = -1.0;
	
	bDoorIsLocked = false;
	/*
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Curves/C_MyCurve"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;*/
}
#pragma endregion

#pragma region BeginPlay
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

	if (SecretSettings.bIsLevelSecret)
	{
		IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (GameInstance->IsSecretAccessible(SecretSettings.GameSecretCode))
			{
				bDoorIsLocked = false;
			}
		}
	}

	TriggerVolume1->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnOverlapBegin);
	TriggerVolume2->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnOverlapBegin);
	TriggerVolume1->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::OnOverlapEnd);
	TriggerVolume2->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::OnOverlapEnd);

	//if (bDoorIsLocked == true)
	//{
	//	return;
	//}
	//
	InitTimeLine();
}
#pragma endregion

#pragma region Tick
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDoorIsUsable == false) return;

	if (AnimationTimeline != NULL)
	{
		AnimationTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

}
#pragma endregion

#pragma region Timer Component
// If the Delay is finished, we close the door again.
void ADoorActor::TimerHandleFinished()
{
	bDoorIsOpen = false;
	AnimationTimeline->ReverseFromEnd();
	Closing();
}
#pragma endregion

#pragma region Timeline Component
void ADoorActor::TimelineCallback(float interpolatedVal)
{
	// Calculate the new doors rotation
	FRotator NewRotation = FRotator(0.0f, InitialRotation + interpolatedVal * MaxTurn * CurrentDirection, 0.0f);
	// Set new rotation to mesh
	Pivot->SetRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
}

void ADoorActor::TimelineFinishedCallback()
{
	if (bDoorIsOpen == false)		
	{
		Closed();
		bDoorIsOpen = false;
	}
}

// Plays the Timeline from the beginning
void ADoorActor::PlayTimeline()
{
	if (AnimationTimeline != NULL)
	{
		AnimationTimeline->PlayFromStart();
	}
}
#pragma endregion

#pragma region Collision Volume
#pragma region On Overlap Begin
void ADoorActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bDoorIsLocked)
	{
		return;
	}

	LOG_DISPLAY(RuntimeExecutionLog, "Overlap Begin!!");
	IDungeonMasterInterface* IsDungeonMaster = Cast<IDungeonMasterInterface>(OtherActor);
	if (!(OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		|| IsDungeonMaster != nullptr))
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Not Player, Not Master!!");
		return;
	}

	if (bDoorIsUsable == false)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Door not usable");
		return;
	}
	if (!bDoorIsOpen)
	{
		
		bDoorCanOpen = true;

		if (OverlappedComponent->GetFName().IsEqual(TriggerVolume1->GetFName()))
			CurrentDirection = DoorOpeningTriggerVolume1;
		else if (OverlappedComponent->GetFName().IsEqual(TriggerVolume2->GetFName()))
			CurrentDirection = DoorOpeningTriggerVolume2;

		if (IsDungeonMaster != nullptr)
		{
			IsDungeonMaster->SetCapsuleRadius(50.f);
			InitTimeLine();
			bDoorCanOpen = true;
			bDoorIsUsable = true;
			bDoorIsLocked = false;
			ICollectableInterface* CollectableRef;
			LeftMouseButtonClicked(CollectableRef);
		}
	}
	Mesh->SetRenderCustomDepth(true);
	Mesh->SetCustomDepthStencilValue(2);
}
#pragma endregion

#pragma region On Overlap End
void ADoorActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	IDungeonMasterInterface* IsDungeonMaster = Cast<IDungeonMasterInterface>(OtherActor);

	if (IsDungeonMaster != nullptr)
	{
		IsDungeonMaster->SetCapsuleRadius(88.f);
	}

	LOG_DISPLAY(RuntimeExecutionLog, "Overlap End!!");
	Mesh->SetRenderCustomDepth(false);
	Mesh->SetCustomDepthStencilValue(0);
	bDoorCanOpen = false;

	if (OverlappedComponent == TriggerVolume1)
	{
		if (!TriggerVolume2->IsOverlappingActor(OtherActor))
		{
			if (bDoorIsOpen == true)
			{
				GetWorldTimerManager().SetTimer(DoorDelayTimerHandle, this, &ADoorActor::TimerHandleFinished, Delay);
			}
		}
		else
		{
			if (!bDoorIsOpen)
			{
				bDoorCanOpen = true;

				if (OverlappedComponent->GetFName().IsEqual(TriggerVolume1->GetFName()))
					CurrentDirection = DoorOpeningTriggerVolume1;
				else if (OverlappedComponent->GetFName().IsEqual(TriggerVolume2->GetFName()))
					CurrentDirection = DoorOpeningTriggerVolume2;
			}
			Mesh->SetRenderCustomDepth(true);
			Mesh->SetCustomDepthStencilValue(2);
		}
	}
	else if (OverlappedComponent == TriggerVolume2)
	{
		if (!TriggerVolume1->IsOverlappingActor(OtherActor))
		{
			if (bDoorIsOpen == true)
			{
		
				GetWorldTimerManager().SetTimer(DoorDelayTimerHandle, this, &ADoorActor::TimerHandleFinished, Delay);
			}
		}
		else
		{
			if (!bDoorIsOpen)
			{
				bDoorCanOpen = true;

				if (OverlappedComponent->GetFName().IsEqual(TriggerVolume1->GetFName()))
					CurrentDirection = DoorOpeningTriggerVolume1;
				else if (OverlappedComponent->GetFName().IsEqual(TriggerVolume2->GetFName()))
					CurrentDirection = DoorOpeningTriggerVolume2;
			}
			Mesh->SetRenderCustomDepth(true);
			Mesh->SetCustomDepthStencilValue(2);
		}
	}

	
}
#pragma endregion
#pragma endregion

#pragma region OpenDoor
void ADoorActor::OpenDoor()
{
	// If there is a timeline and it is not playing
	if (AnimationTimeline != NULL && !AnimationTimeline->IsPlaying())
	{

		LOG_DISPLAY(RuntimeExecutionLog, "Playing Timeline!!");
		// set flag to open door
		bDoorIsOpen = true;
		// Play the timeline
		PlayTimeline();
		// Call Blueprint Event
		Opening();
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Not Playing Timeline!!");
	}
}
#pragma endregion
void ADoorActor::InitTimeLine()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

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

		bDoorIsOpen = false;
		bDoorCanOpen = false;

		if (!TriggerVolume1)
		{
			LOG_WARNING(InitializationLog, "TriggerVolume1 not found.\nThis shouldn't happen!");
			return;
		}

		InitialRotation = GetActorRotation().Yaw;
	}
}

#pragma region Left MouseButton Clicked
void ADoorActor::LeftMouseButtonClicked(ICollectableInterface* &CollectableRef)
{
	if (bDoorIsUsable == false) return;

	if(bDoorCanOpen)
		OpenDoor();

	LOG_DISPLAY(RuntimeExecutionLog, "Opening Door!!");
}
#pragma endregion

#pragma region Set Door Enabled
void ADoorActor::SetDoorEnabled(bool CanBeUsed)
{
	bDoorIsUsable = CanBeUsed;
}
#pragma endregion

#pragma region Get Door Level
TEnumAsByte<EPartInformation> ADoorActor::GetDoorLevel() const
{
	return DoorLevel;
}
#pragma endregion

void ADoorActor::OpenDoorByMaster()
{
	bDoorIsUsable = true;
	bDoorIsLocked = false;
}