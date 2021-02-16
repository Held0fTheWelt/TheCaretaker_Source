/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Characters/Spider/SpiderCharacter.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/AnimationAsset.h"
#include "Log/GlobalLog.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"

ASpiderCharacter::ASpiderCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	if (AudioComponent == nullptr)
		AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("AudioComponent"));

	if (NotificationTrigger == nullptr)
		NotificationTrigger = CreateDefaultSubobject<USphereComponent>(FName("NotificationSphere"));
		
	// This is a query only trigger volume
	NotificationTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	NotificationTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	NotificationTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	NotificationTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);


	NotificationTrigger->SetupAttachment(RootComponent);
	NotificationTrigger->SetRelativeLocation(FVector(0.f, 0.f, -65.f));
	NotificationTrigger->SetSphereRadius(85.f, true);

	PostProcessingVolumeName = "PostProcessVolume_Invisibility";

}


void ASpiderCharacter::RegisterMarkerWidget(bool Register)
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
		LOG_DISPLAY(InitializationLog, "Marker Widget for Actor on Map setup okay!");
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

float ASpiderCharacter::SetAnimRate(float AnimRate)
{
	float WalkAnimRate = GetMesh()->GlobalAnimRateScale;
	GetMesh()->GlobalAnimRateScale = AnimRate;
	return WalkAnimRate;
}

float ASpiderCharacter::SetMoveSpeed(float MoveSpeed)
{
	float WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	return WalkSpeed;
}


void ASpiderCharacter::BeginPlay()
{
	Super::BeginPlay();
		
	if (AudioComponent == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find AudioComponent in Spider. This shouldn't happen !")
		return;
	}
	else
	{
		if (SpiderAttackSound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Couldn't find Spider Attack Sound in Spider. Is it set up in the blueprint ?")
			return;
		}
		else
		{
			AudioComponent->SetSound(SpiderAttackSound);
		}
	}

	if (GetCapsuleComponent() != nullptr)
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASpiderCharacter::OnOverlapBegin);
	}
	
	if (NotificationTrigger != nullptr)
	{
		NotificationTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASpiderCharacter::NotifyOnOverlapBegin);
	}
	else
	{
		LOG_WARNING(InitializationLog,"Could not find Notification Trigger ! This shouldn't happen !")
	}

	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
	}
	else
	{
		FSpiderSetup SpiderSetup = GameInstance->GetSpiderSetup();

		Movement->MaxWalkSpeed = SpiderSetup.WalkSpeed;
	}

	RegisterMarkerWidget(true);
}

void ASpiderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpiderCharacter::SetGamePaused(bool SetGamePaused)
{
	bPaused = SetGamePaused;
}

bool ASpiderCharacter::IsPaused() const
{
	return bPaused;
}

void ASpiderCharacter::SetPatrolPoints(TArray<class AConnectedTargetPoint*> NewPatrolPoints)
{
	PatrolPoints = NewPatrolPoints;
}

void ASpiderCharacter::Tick(float DeltaTime)
{
	if (bPaused) return;
	Super::Tick(DeltaTime);
}

void ASpiderCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		TArray<AActor*> Actors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), Actors);

		for (auto Actor : Actors)
		{
			if (Actor->GetName() == PostProcessingVolumeName)
			{
				APostProcessVolume* Volume = Cast<APostProcessVolume>(Actor);
				if (Volume == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "Could not get Post Processing Volume for PowerUp Effect")
				}
				else
				{
					if (Volume->bEnabled)
					{
						return;
					}
				}
			}
		}

		AudioComponent->Play();
	
		ICharacterInterface* Character = Cast<ICharacterInterface>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (Character == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Couldn't find Character interface! This shouldn't happen !")
		}
		else
		{
			SetActorRotation(Character->GetDeathSpawnRotation());
			SetActorLocation(Character->GetDeathSpawnLocation());
			GetMesh()->SetRelativeLocation(FVector(0));
			GetMesh()->SetRelativeRotation(FRotator(0, 0, 0));
		}
		
		if (FightAnimation == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Couldn't play fight animation! Is it set up in the spiders blueprint ?")
		}
		else
		{
			GetMesh()->PlayAnimation(FightAnimation, false);
		}

		IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (Menu == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
		}
		else
		{
			Menu->OpenIngameMenu(EIngameMenuCall::IMC_DEATHBYSPIDER);
		}

		IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (AchievementInstance == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
				return;
		}

		AchievementInstance->CountAchievement(EAchievementType::AT_DEATHBYSPIDER);
	}
}

void ASpiderCharacter::NotifyOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

