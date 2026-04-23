// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "HealthComponent.h"
// Sets default values
AHealthPickup::AHealthPickup()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("HealthPickupSceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthPickupMeshComponent"));

	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap); //Set Mesh Collision to Overlap

	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);

}

void AHealthPickup::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<ATopDownCharacter>(OtherActor))
	{
		ATopDownCharacter* Player = Cast<ATopDownCharacter>(OtherActor);

		// Get the  health component by class
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();

		if (HealthComponent)
		{
			// Call the pickup function on the component
			HealthComponent->HealthPickedUp();
		}
		Destroy();
	}

}


