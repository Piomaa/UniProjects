//NOT IN USE
//NOT IN USE
//NOT IN USE
//NOT IN USE

#include "BTRoaming.h"
#include "BehaviorTree//BlackboardComponent.h"

#include "AIController.h"

#include "Misc/OutputDeviceDebug.h"

#include "AIController.h"
#include "NavigationSystem.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTRoaming::UBTRoaming()
{
	NodeName = "roaming";
}

EBTNodeResult::Type UBTRoaming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();

	bool b_RandomPoint = Blackboard->GetValueAsBool("RandomPoint");

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();

	FVector Origin = Pawn->GetActorLocation();

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(AIController);
	FNavLocation RandomNavLocation;

	FVector Location;

	if (NavSys && NavSys->GetRandomPointInNavigableRadius(Origin, 1000, RandomNavLocation))
	{
		Location = RandomNavLocation.Location;
		//UE_LOG(LogTemp, Warning, TEXT("GaveLocation"));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow,
			FString::Printf(TEXT("Gave Location")));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow,
			FString::Printf(TEXT("Gave 11111")));
		Blackboard->SetValueAsBool(RandomPointDestinationKey.SelectedKeyName, true);
		AIController->MoveToLocation(Location);
		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}
