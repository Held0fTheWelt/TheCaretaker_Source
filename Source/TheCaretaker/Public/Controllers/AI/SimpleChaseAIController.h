/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SimpleChaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ASimpleChaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASimpleChaseAIController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void StopMovement() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBlackboardComponent* BlackBoardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBlackboardData * ChaseBlackBoard;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* ChaseBehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName KeyName;
private:
	bool bSetupOkay;
};
