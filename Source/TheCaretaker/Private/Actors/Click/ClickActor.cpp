/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/Click/ClickActor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "UObject/ConstructorHelpers.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
// Sets default values
AClickActor::AClickActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	if (!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolumeComponent"));

	// This is a query only trigger volume
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetBoxExtent(FVector(60.f, 60.f, 80.f));

	RootComponent = TriggerVolume;

	if (!Mesh)
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupComponent"));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -60.f));

	Mesh->SetupAttachment(RootComponent);


}

void AClickActor::LeftMouseClicked()
{
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetVisibility(false, true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
#pragma endregion

#pragma region Begin Play
void AClickActor::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerVolume)
	{
		LOG_WARNING(InitializationLog, "TriggerVolume not found.\nThis shouldn't happen!");
		return;
	}
	else
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AClickActor::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AClickActor::OnOverlapEnd);
	}
}
#pragma endregion

#pragma region Left MouseButton Clicked
void AClickActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	LeftMouseClicked();
	CollectableRef = this;
}
#pragma endregion

#pragma region Get Actor
AActor* AClickActor::GetActor()
{
	return this;
}
#pragma endregion

#pragma region Trigger Volume
#pragma region On Overlap Begin
void AClickActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		return;
	}


	Mesh->SetRenderCustomDepth(true);
	Mesh->SetCustomDepthStencilValue(2);
}
#pragma endregion

#pragma region On Overlap End
void AClickActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Mesh->SetRenderCustomDepth(false);
	Mesh->SetCustomDepthStencilValue(0);
}
#pragma endregion
#pragma endregion