//NOT IN USE
//NOT IN USE
//NOT IN USE
//NOT IN USE
#include "BTfindPlayer.h"
#include "Kismet/GameplayStatics.h"

#include "BehaviorTree//BlackboardComponent.h"

#include "AIController.h"

#include "Misc/OutputDeviceDebug.h"

UBTfindPlayer::UBTfindPlayer()
{
	NodeName = "Find Player";
	DetectRadius = 600.0f;
}

EBTNodeResult::Type UBTfindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	float distance = FVector::Dist(Player->GetActorLocation(), Pawn->GetActorLocation());

	if (distance <= DetectRadius)
	{
		auto Blackboard = OwnerComp.GetBlackboardComponent();
		Blackboard->SetValueAsObject(Playerkey.SelectedKeyName, Player);
		Blackboard->SetValueAsBool(FName("b_FoundPlayer"), true);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
