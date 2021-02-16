/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/PressurePlate/PressurePlate.h"

#include "TimerManager.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
//
//#include "Mechanics/MovingPlatform/MovingPlatform.h"

#pragma region Default Constructor
// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolumeComponent"));
	if(!Mesh)
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateComponent"));
		
	
	// Remember nullptr checks !!!
	//if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;

	// This is a query only trigger volume
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetBoxExtent(FVector(50.f, 50.f, 100.f));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, .25f));
	//const ConstructorHelpers::FObjectFinder<UStaticMesh> BoxObj(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	//PressurePlate->SetStaticMesh(BoxObj.Object);

	Mesh->SetupAttachment(RootComponent);

	Delay = 2.0f;
}
#pragma endregion

#pragma region BeginPlay
// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	bSwitchIsOn = false;

	if (!TriggerVolume)
	{
		UE_LOG(LogTemp, Warning, TEXT("TriggerVolume not found.\nThis shouldn't happen!"));
		return;
	}

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}
#pragma endregion

#pragma region Tick
// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
#pragma endregion

#pragma region OnOverlapBegin
void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	bSwitchIsOn = true;
	//for (AMovingPlatform* platform : PlatformsToTrigger)
	//{
	//	platform->AddActiveTrigger();
	//}
}
#pragma endregion

#pragma region OnOverlapEnd
void APressurePlate::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bSwitchIsOn = false;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APressurePlate::TimerHandleFinished, Delay);
}
#pragma endregion

#pragma region TimerHandle Finished
void APressurePlate::TimerHandleFinished()
{
	if (!bSwitchIsOn)
	{
		//for (AMovingPlatform* platform : PlatformsToTrigger)
		//{
		//	platform->RemoveActiveTrigger();
		//}
	}
}
#pragma endregion