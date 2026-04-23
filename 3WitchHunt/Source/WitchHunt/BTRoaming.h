//NOT IN USE
//NOT IN USE
//NOT IN USE
//NOT IN USE
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTRoaming.generated.h"

/**
 * 
 */
UCLASS()
class WITCHHUNT_API UBTRoaming : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTRoaming();
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector RandomPointDestinationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};