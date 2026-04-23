// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTCheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class WITCHHUNT_API UBTCheckDistance : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTCheckDistance();

	// for the blackboard bool that we want to change
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBBool;

	// the black board object, in this case the player, which is what we find the distance to
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBPlayer;

	// a float thats changable in the editor, which is the distance we want to compare to in this node task
	UPROPERTY(EditAnywhere)
	float Distance;

	// a bool detmerning whether we want to check if the distance is below or above what we want
	UPROPERTY(EditAnywhere)
	bool Above;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
