// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	SetIsReplicatedByDefault(true); // Ensure the component itself replicates
	Health = 100.f;
}



void UHealthComponent::TakeDamage(float Damage)
{

	Health -= Damage; // reduce health by set amount
	OnDamageTaken.Broadcast(); // broadcast event for blueprint use
	Multicast_OnDamageTaken_Implementation(); // broadcast for all clients
	if (Health <= 0)
	{
		Death(); // handle death
	}
}

void UHealthComponent::Death()
{
	OnDeath.Broadcast(); // broadcast event for blueprint use
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const // gotta be honest i am not sure what this does, but it's related to replication
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, Health);
}

void UHealthComponent::Multicast_OnDamageTaken_Implementation()
{
	OnDamageTaken.Broadcast(); // Call the event to be received by clients
}

float UHealthComponent::GetCurrentHealth() { // blueprint pure function, used for retreiving health for UI purposes 
	return Health;
}

void UHealthComponent::HealthPickedUp()
{
	Health = FMath::Min(Health + 30.f, 100.f);
}
