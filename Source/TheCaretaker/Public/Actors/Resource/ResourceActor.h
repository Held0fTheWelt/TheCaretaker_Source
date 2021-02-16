/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Click/ClickActor.h"
#include "Enums/ResourceType/ResourceType.h"
#include "ResourceActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FResourceCollected, int8, Amount, AResourceActor*, Actor);

UCLASS()
class THECARETAKER_API AResourceActor : public AClickActor
{
	GENERATED_BODY()

public:
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Resource")
	void AddResourceEvent();
protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 AmountToAdd = 1;
private:
	FResourceCollected ResourceCollected;
};
