/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Characters/FirstPerson/FirstPersonCharacter.h"

#include "SlateApplication.h"


#include "Actors/Monsters/MonsterFeedingVolumeActor.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Widgets/Main/MainUI.h"
#include "Widgets/NoiseBar/NoiseBarUserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

#pragma region Constructor
AFirstPersonCharacter::AFirstPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);				// Set so only owner can see mesh
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);	// Attach mesh to FirstPersonCameraComponent
	Mesh1P->bCastDynamicShadow = false;			// Disallow mesh to cast dynamic shadows
	Mesh1P->CastShadow = false;				// Disallow mesh to cast other shadows

	RunSpeedModifier = 2;

	NoiseBar = UNoiseBarUserWidget::StaticClass();

	if (DeathSpawnPoint == nullptr)
		DeathSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("DeathSpawnPoint"));

	DeathSpawnPoint->SetRelativeLocation(FVector(0, 0, 0));

	DeathSpawnPoint->SetupAttachment(RootComponent);

	LineTraceLength = 400.f;
	TimeDilationValue = 1.f;

}
#pragma endregion

#pragma region Begin Play
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	TArray<AActor*> Monsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterFeedingVolumeActor::StaticClass(), Monsters);

	for (AActor* Actor : Monsters)
	{
		AMonsterFeedingVolumeActor* Monster = Cast<AMonsterFeedingVolumeActor>(Actor);
		if (Monster == nullptr)
		{
			LOG_WARNING(InitializationLog,"Could not cast Actor to Monster! This shouldn't happen !")
			continue;
		}
		else
		{
			Monster->MonsterAngry.AddDynamic(this, &AFirstPersonCharacter::PlayMonsterSound);
		}
	}

	GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog,"Could not find GameInstance ! This shouldn't happen !")
	}
	else
	{
		FCharacterSetup CharacterSetup = GameInstance->GetCharacterSetup();

		Movement->MaxWalkSpeed = CharacterSetup.WalkSpeed;
		RunSpeedModifier = CharacterSetup.RunModifier;
	}
	WalkSpeedValue = WalkSpeed = Movement->MaxWalkSpeed;
}
#pragma endregion

void AFirstPersonCharacter::PlayMonsterSound(USoundBase* MonsterSound)
{
	if (MonsterSound != nullptr)
	{
		UGameplayStatics::SpawnSoundAttached(MonsterSound, GetCapsuleComponent(), EName::NAME_None, GetFirstPersonCameraComponent()->GetComponentLocation(), EAttachLocation::SnapToTarget,false, 1, 1, 0, nullptr, nullptr, true);
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not play MonsterSound, because it was null!")
	}
}

void AFirstPersonCharacter::SetSpeedValue(float NewSpeed)
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = NewSpeed;
	WalkSpeedValue = WalkSpeed = NewSpeed;
}
#pragma region Left MouseButton
void AFirstPersonCharacter::LeftMouseButton(ICollectableInterface* &Collectable, bool &PickupCollected)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - no game influence of MouseClick");
		return;
	}

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (LineTraceLength * FirstPersonCameraComponent->GetForwardVector());

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredComponent(GetMesh());
	FCollisionResponseParams ResponseParams;
	

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params, ResponseParams))
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "HitActor was null ! This shouldn't happen !")
			return;
		}

		IMouseInteractionInterface* MouseInteraction = Cast<IMouseInteractionInterface>(HitActor);

		if (MouseInteraction == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName())
			LOG_DISPLAY(RuntimeExecutionLog,"MouseInteractionInterface not present !")

			if (PickupCollected)
			{
				if (GameInstance == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "GameInstance was null ! This shouldn't happen !")
				}
				else
				{
					GameInstance->PickupDropped(HitResult.Location);
					PickupCollected = false;
				}
			}
		}
		else
		{
			MouseInteraction->LeftMouseButtonClicked(Collectable);
		}
	}
}
#pragma endregion

#pragma region Right MouseButton
void AFirstPersonCharacter::RightMouseButton()
{
}

#pragma endregion
void AFirstPersonCharacter::SetGamePaused(bool SetGamePaused)
{
	bIsPaused = SetGamePaused;
}

bool AFirstPersonCharacter::IsPaused() const
{
	return bIsPaused;
}

void AFirstPersonCharacter::Jump()
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not jumping");
		return;
	}

	Super::Jump();
}

void AFirstPersonCharacter::StopJumping()
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not stopping jump");
		return;
	}

	Super::StopJumping();
}

void AFirstPersonCharacter::AddControllerYawInput(float Input)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not turning");
		return;
	}

	Super::AddControllerYawInput(Input * TimeDilationValue);
}

void AFirstPersonCharacter::AddControllerPitchInput(float Input)
{
	if (bIsPaused)
	{
	//	LOG_DISPLAY(RuntimeExecutionLog, "Game Is Paused - not looking up");
		return;
	}

	Super::AddControllerPitchInput(Input * TimeDilationValue);
}

FVector AFirstPersonCharacter::GetDeathSpawnLocation() const
{
	return DeathSpawnPoint->GetComponentLocation();
}

FRotator AFirstPersonCharacter::GetDeathSpawnRotation() const
{
	return DeathSpawnPoint->GetComponentRotation();
}

void AFirstPersonCharacter::SetSpeedMultiplier(float SpeedMultiplier)
{
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());

	if (MovementComponent == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not cast MovementComponent ! This shouldn't happen !")
	}
	else
	{
		WalkSpeed = WalkSpeedValue * SpeedMultiplier;
		MovementComponent->MaxWalkSpeed = WalkSpeed;
	}	
}

FVector AFirstPersonCharacter::GetLocation() const
{
	return GetActorLocation();
}

void AFirstPersonCharacter::IsDilatingTime(float Value)
{
	TimeDilationValue = Value;
}
