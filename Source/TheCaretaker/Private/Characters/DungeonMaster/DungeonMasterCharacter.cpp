/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "DungeonMasterCharacter.h"

#include "TimerManager.h"

#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Controllers/AI/SimpleChaseAIController.h"
#include "Engine/World.h"
#include "Interfaces/Door/DoorInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Log/GlobalLog.h"

ADungeonMasterCharacter::ADungeonMasterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	if (SoundComponent == nullptr)
		SoundComponent = CreateDefaultSubobject<UAudioComponent>(FName("SoundComponent"));

	SoundComponent->SetUISound(true);

	SoundComponent->SetupAttachment(RootComponent);

	if (SphereComponent == nullptr)
		SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));

	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetRelativeLocation(FVector(450.f,0.f,0.f));

	GrollDelay = 1.8f;
}

void ADungeonMasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADungeonMasterCharacter::OnOverlapBegin);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADungeonMasterCharacter::OnOverlapBegin);
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ADungeonMasterCharacter::OnOverlapBegin);

	if (RoarSound != nullptr)
	{
		SoundComponent->Sound = RoarSound;
		SoundComponent->Play();
	}

	bCanChange = true;
}

void ADungeonMasterCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	IDoorInterface* IsDoor = Cast<IDoorInterface>(OtherActor);

	if (IsDoor)
	{
		IsDoor->OpenDoorByMaster();
		LOG_WARNING(RuntimeExecutionLog, "OpeningDoor.")
		return;
	}

	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		AController* PlayerController = OtherActor->GetInstigatorController();

		if (PlayerController == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Controller was null ! This shouldn't happen !")
		}
		else
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(OtherActor->GetActorLocation(), GetActorLocation());
			PlayerController->ClientSetRotation(Rotator, true);
		}


		if (CharacterDead.IsBound())
		{
			LOG_DISPLAY(RuntimeExecutionLog, "Character dead.")
			CharacterDead.Execute();
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "CharacterDead Event not bound.")
		}

		if (RoarSound != nullptr)
		{
			SoundComponent->Sound = RoarSound;
			SoundComponent->Play();
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayGroll, this, &ADungeonMasterCharacter::DelayedGroll, 1.0f, false, GrollDelay);

		ASimpleChaseAIController* AIController = Cast<ASimpleChaseAIController>(GetController());

		if (AIController == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not find AI Controller ! This shouldn't happen !")
		}
		else
		{
			AIController->StopMovement();
		}

		GetMesh()->GlobalAnimRateScale = .3f;
	}
}

void ADungeonMasterCharacter::DelayedGroll()
{
	if (GrollSound != nullptr)
	{
		SoundComponent->Sound = GrollSound;
		SoundComponent->Play();
	}
}

void ADungeonMasterCharacter::SetCapsuleRadius(float Radius)
{
	if (bCanChange == false)
	{
		return;
	}

	GetCapsuleComponent()->SetCapsuleRadius(Radius, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayGroll, this, &ADungeonMasterCharacter::CanChangeAgain, 1.0f, true, 1.f);

	bCanChange = false;
}

void ADungeonMasterCharacter::CanChangeAgain()
{
	bCanChange = true;
}
