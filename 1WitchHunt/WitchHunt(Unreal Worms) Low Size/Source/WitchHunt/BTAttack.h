// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTAttack.generated.h"


UCLASS()
class WITCHHUNT_API UBTAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTAttack();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBPlayer;

	// a float thats changable in the editor, letting us set the enemies attack damage to what we want it
	UPROPERTY(EditAnywhere)
	float Damage;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
