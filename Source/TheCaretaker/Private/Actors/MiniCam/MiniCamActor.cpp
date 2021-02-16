/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors\MiniCam\MiniCamActor.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.H"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/ActorMarker/ActorMarkerWidgetInterface.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

#pragma region Constructor
AMiniCamActor::AMiniCamActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerPawn = nullptr;

	AmountOfZoomChange = 64;
	ZoomMin = 512;
	ZoomMax = 2048;

	GetCaptureComponent2D()->SetRelativeLocation(FVector(0.f, 0.f, 900.f));
	GetCaptureComponent2D()->SetRelativeRotation(FRotator(-90.f,0.f,0.f));

	GetCaptureComponent2D()->ProjectionType = ECameraProjectionMode::Orthographic;
	GetCaptureComponent2D()->OrthoWidth = 768;
	GetCaptureComponent2D()->CaptureSource = ESceneCaptureSource::SCS_BaseColor;

	bIsTutorialMode = false;
	bMapFailure = false;
}
#pragma endregion

#pragma region Begin Play
void AMiniCamActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	CurrentZoom = GetCaptureComponent2D()->GetComponentLocation().Z;

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController == nullptr)
	{
		LOG_WARNING(InitializationLog, "PlayerController was null")
		return;
	}

	EnableInput(PlayerController);

	if (InputComponent)
	{
		InputComponent->BindAxis("Zoom", this, &AMiniCamActor::ZoomMapCamera);
	}


	if (PlayerPawn == nullptr)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		if (PlayerPawn == nullptr)
		{
			LOG_WARNING(RuntimeLog, "PlayerPawn was null")
			return;
		}
	}

	ITutorialInterface* TutorialGameMode = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (TutorialGameMode != nullptr)
	{
		bIsTutorialMode = true;
	}
}
#pragma endregion

#pragma region Tick
void AMiniCamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location;
	FRotator Rotation;

	if (bMapFailure)
	{
		Location.X = -PlayerPawn->GetActorLocation().X;
		Location.Y = -PlayerPawn->GetActorLocation().Y;
		Rotation.Yaw = -PlayerPawn->GetViewRotation().Yaw;
	}
	else
	{
		Location.X = PlayerPawn->GetActorLocation().X;
		Location.Y = PlayerPawn->GetActorLocation().Y;
		Rotation.Yaw = PlayerPawn->GetViewRotation().Yaw;
	}

	Location.Z = GetActorLocation().Z;
	Rotation.Pitch = 0;
	Rotation.Roll = 0;

	SetActorLocation(Location);
	SetActorRotation(Rotation);

	if (ActorMarkers.Num() == 0)
	{
		if (!bIsTutorialMode)
		{
			LOG_DISPLAY(RuntimeLog, "Monster Markers were 0 count")
		}
		return;
	}

	for (auto Marker : ActorMarkers)
	{
		Marker->IsHiddenInGame();
		Marker->UpdatePosition(Location, Rotation.GetInverse());		
	}
}

#pragma endregion

float AMiniCamActor::RegisterActorMarker(IActorMarkerWidgetInterface* Marker, bool Register)
{
	if (Register)
	{
		if (Marker != nullptr)
		{
			ActorMarkers.Add(Marker);
			return 2048 / CurrentZoom;
		}
		else
		{
			LOG_WARNING(InitializationLog, "Cannot register MonsterMarker, because interface was null! This shouldn't happen")
			return 0;
		}
	}
	else
	{
		if (Marker != nullptr)
		{
			if (ActorMarkers.Contains(Marker))
			{
				ActorMarkers.Remove(Marker);
			}
			else
			{
				LOG_WARNING(InitializationLog, "Cannot unregister MonsterMarker, because it was not in List! This shouldn't happen")
			}
		}
		else
		{
			LOG_WARNING(InitializationLog, "Cannot unregister MonsterMarker, because interface was null! This shouldn't happen")
		}
		return 0;
	}
}


#pragma region Zoom Map Camera
void AMiniCamActor::ZoomMapCamera(float Value)
{
	if (Value > 0)
	{
		CurrentZoom -= AmountOfZoomChange;
	}
	else if (Value < 0)
	{
		CurrentZoom += AmountOfZoomChange;			
	}

	CurrentZoom = FMath::Clamp(CurrentZoom, ZoomMin, ZoomMax);

	GetCaptureComponent2D()->SetRelativeLocation(FVector(0, 0, CurrentZoom));

	for (auto Marker : ActorMarkers)
	{
		Marker->SetScaleFactor(2048 / CurrentZoom);
	}
}
#pragma endregion

#pragma region Set Map Failure
void AMiniCamActor::SetMapFailure(bool HasFailure)
{
	bMapFailure = HasFailure;
	LOG_WARNING(RuntimeExecutionLog,"Setting Failure Flag")
}
#pragma endregion
