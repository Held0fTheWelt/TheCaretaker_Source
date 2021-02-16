/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "ActorMarkerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/Widget.h"
#include "Engine/World.h"
#include "Interfaces/MiniMapActor/MiniMapActorInterface.h"
#include "Interfaces/Widgets/MiniMap/MiniMapInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Log/GlobalLog.h"

UActorMarkerWidget::UActorMarkerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ClampLength = 200;

	RandomJitterMin = FVector2D(-5, -5);
	RandomJitterMax = FVector2D(5, 5);

	RandomRelocMin = FVector2D(-20, -20);
	RandomRelocMax = FVector2D(20, 20);

	TimeToChangeMin = 2;
	TimeToChangeMax = 5;

}

void UActorMarkerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClampLengthSquared = ClampLength * ClampLength;
}

void UActorMarkerWidget::SetSize(FVector2D NewSize)
{
	MarkerSizeBox->SetWidthOverride(NewSize.X);
	MarkerSizeBox->SetHeightOverride(NewSize.Y);
}

void UActorMarkerWidget::SetActorImage(UTexture2D* Texture)
{
	ActorImage->SetBrushFromSoftTexture(Texture);
}

void UActorMarkerWidget::SetActor(AActor* ThisActor)
{
	Actor = ThisActor;
}

void UActorMarkerWidget::SetScaleFactor(float ScaleFactor)
{
	Scale = ScaleFactor;
}

void UActorMarkerWidget::UpdatePosition(FVector PlayerLocation, FRotator PlayerRotation)
{
	if (Actor == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Update Position, because Monster Actor was null !")
		return;
	}

	CurrentPosition = PlayerLocation - Actor->GetActorLocation();
	

	CurrentPosition = PlayerRotation.RotateVector(CurrentPosition);

	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	CanvasSlot->SetPosition(GetCurrentPosition());
	this->Slot = CanvasSlot;
	this->Slot->MarkPackageDirty();
}

void UActorMarkerWidget::SetMiniMapInterface(IMiniMapInterface* Map)
{
	MiniMap = Map;

	MiniMap->GetVectorLength();
}

FVector2D UActorMarkerWidget::GetCurrentPosition() 
{		
	FVector2D Current  = FVector2D(-CurrentPosition.Y, CurrentPosition.X);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), Current.X / 10 * Scale);
	FVector2D ReturnValue = Current / 10 * Scale;;

	if (bAddJitterToWidget)
	{
		ReturnValue += (CurrentReloc + CurrentJitter);
		SecondCount++;
		if (SecondCount % 20 == 0)
		{
			SecondCount = 0;
			CurrentJitter = FVector2D(FMath::RandRange(RandomJitterMin.X, RandomJitterMax.X), FMath::RandRange(RandomJitterMin.Y, RandomJitterMax.Y));
		}
		CurrentTimeToChange += GetWorld()->GetDeltaSeconds();
		if (CurrentTimeToChange >= NextTimeToChange)
		{
			CurrentTimeToChange = 0;
			NextTimeToChange = FMath::RandRange(TimeToChangeMin, TimeToChangeMax);
			CurrentReloc = FVector2D(FMath::RandRange(RandomRelocMin.X, RandomRelocMax.X), FMath::RandRange(RandomRelocMin.Y, RandomRelocMax.Y));
		}
	}

	if (MiniMap == nullptr)
	{
		LOG_WARNING(RuntimeLog, "MiniMap was null ! This shouldn't happen !")
	}
	else
	{	
		//UE_LOG(LogTemp, Warning, TEXT("%f"), ClampLength);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), ReturnValue.SizeSquared());

		if (ReturnValue.SizeSquared() >= ClampLengthSquared)
		{
			//LOG_DISPLAY(RuntimeExecutionLog, "Clamping Values")
			//UE_LOG(LogTemp, Warning, TEXT("%f"), ReturnValue.X);
			return ReturnValue.GetSafeNormal() * ClampLength;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), ReturnValue.X);
	return ReturnValue;
}

void UActorMarkerWidget::InitializePosition()
{
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	FAnchors Anchors;
	Anchors.Minimum = FVector2D(.5f, .5f);
	Anchors.Maximum = FVector2D(.5f, .5f);

	CanvasSlot->SetAnchors(Anchors);
	CanvasSlot->SetSize(FVector2D(50, 50));
	CanvasSlot->SetAlignment(FVector2D(.5f, .5f));
	CanvasSlot->SetPosition(FVector2D(0, 0));

	this->Slot = CanvasSlot;
}

void UActorMarkerWidget::IsHiddenInGame() 
{
	if (Actor == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Monster Actor was null !")
		return;
	}

	if (Actor->IsHidden())
	{
		MarkerImage->SetVisibility(ESlateVisibility::Hidden);
		ActorImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		MarkerImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		ActorImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UActorMarkerWidget::AddJitterToMapWidget(bool AddJitter)
{
	bAddJitterToWidget = AddJitter;

	if (bAddJitterToWidget)
	{
		NextTimeToChange = FMath::RandRange(TimeToChangeMin, TimeToChangeMax);
		CurrentReloc = FVector2D(FMath::RandRange(RandomRelocMin.X, RandomRelocMax.X), FMath::RandRange(RandomRelocMin.Y, RandomRelocMax.Y));
		CurrentJitter = FVector2D(FMath::RandRange(RandomJitterMin.X, RandomJitterMax.X), FMath::RandRange(RandomJitterMin.Y, RandomJitterMax.Y));
		SecondCount = FMath::RandRange(0, 19);
	}
}

void UActorMarkerWidget::RegisterActorMarkerWidget()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMiniMapActorInterface::StaticClass(), Actors);

	for (AActor* ThisActor : Actors)
	{
		IMiniMapActorInterface* MiniMapActor = Cast<IMiniMapActorInterface>(ThisActor);

		if (MiniMapActor != nullptr)
		{
			SetScaleFactor(MiniMapActor->RegisterActorMarker(this, true));
		}
	}
}

void UActorMarkerWidget::UnregisterActorMarkerWidget()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMiniMapActorInterface::StaticClass(), Actors);

	for (AActor* ThisActor : Actors)
	{
		IMiniMapActorInterface* MiniMapActor = Cast<IMiniMapActorInterface>(ThisActor);

		if (MiniMapActor != nullptr)
		{
			MiniMapActor->RegisterActorMarker(this, false);
		}
	}
}

void UActorMarkerWidget::SetIsAngry(bool IsAngry)
{
	bIsAngry = IsAngry;
}

bool UActorMarkerWidget::IsAngry() const
{
	return bIsAngry;
}
void UActorMarkerWidget::SetIsMonster(bool IsMonster)
{
	bIsMonster = IsMonster;
}