/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ActorMarker/ActorMarkerWidgetInterface.h"
#include "ActorMarkerWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UActorMarkerWidget : public UUserWidget , public IActorMarkerWidgetInterface
{
	GENERATED_BODY()
	
public:
	UActorMarkerWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* MarkerSizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* MarkerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ActorImage;

public:
	void SetSize(FVector2D Size);
	void SetActorImage(class UTexture2D* Texture);
	void SetActor(class AActor* Actor);
	void SetMiniMapInterface(class IMiniMapInterface* Map);
	void SetIsAngry(bool IsAngry);
	void SetIsMonster(bool IsMonster);
	bool IsAngry() const;

	void RegisterActorMarkerWidget();
	void UnregisterActorMarkerWidget();
	
	virtual void SetScaleFactor(float ScaleFactor) override;
	virtual void UpdatePosition(FVector PlayerLocation, FRotator PlayerRotation) override;
	virtual FVector2D GetCurrentPosition() override;
	
	void InitializePosition();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void PlayWidgetAnimation(int32 Animation);

protected:
	int32 Size;
	int32 Index;
	float Scale;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Monster")
	bool bIsMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Monster")
	bool bIsAngry;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ClampLength;

	UPROPERTY(BlueprintReadonly)
	class AActor* Actor;

	UPROPERTY(EditDefaultsOnly, Category = "Jitter")
	FVector2D RandomJitterMin;
	UPROPERTY(EditDefaultsOnly, Category = "Jitter")
	FVector2D RandomJitterMax;
	UPROPERTY(EditDefaultsOnly, Category = "Jitter")
	FVector2D RandomRelocMin;
	UPROPERTY(EditDefaultsOnly, Category = "Jitter")
	FVector2D RandomRelocMax;

	UPROPERTY(EditDefaultsOnly, Category = "Jitter")
	float TimeToChangeMin;
	UPROPERTY(EditDefaultsOnly, Category = "Jitter")
	float TimeToChangeMax;

private:
	class IMiniMapInterface* MiniMap;

	FVector CurrentPosition;
	float CanvasSize;
	float ClampLengthSquared;

	virtual void IsHiddenInGame() override;
	virtual void AddJitterToMapWidget(bool AddJitter) override;

	bool bAddJitterToWidget;
	float CurrentTimeToChange;
	float NextTimeToChange;
	FVector2D CurrentReloc;
	FVector2D CurrentJitter;
	int32 SecondCount;
};
