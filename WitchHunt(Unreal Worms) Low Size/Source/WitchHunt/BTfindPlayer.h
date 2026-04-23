//NOT IN USE
//NOT IN USE
//NOT IN USE
//NOT IN USE

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTfindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class WITCHHUNT_API UBTfindPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTfindPlayer();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Playerkey;
	UPROPERTY(EditAnywhere)

	FBlackboardKeySelector foundPlayer;
	UPROPERTY(EditAnywhere)
	float DetectRadius;


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
