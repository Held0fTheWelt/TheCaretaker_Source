/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecretLockActor.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretInformation
{
	GENERATED_BODY()

public:
	FSecretInformation();

public:
	UPROPERTY(EditAnywhere)
	bool bIsLevelSecret;

	UPROPERTY(EditAnywhere)
	FString GameSecretCode;

	UPROPERTY(EditAnywhere, Category = "Secret Actors")
	TArray<class AActor*> ActorsBoundToSecret;
};

UCLASS()
class THECARETAKER_API ASecretLockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecretLockActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Settings")
	FSecretInformation SecretSettings;

};
