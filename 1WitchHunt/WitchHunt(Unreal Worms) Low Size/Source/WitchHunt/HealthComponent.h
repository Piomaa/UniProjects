// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WITCHHUNT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();


public:	

		UFUNCTION(BluePrintCallable, Category = "Health")
		void TakeDamage(float Damage);

		UFUNCTION(BlueprintCallable, Category = "Health")
		void Death();

		UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnDeath OnDeath; // Blueprint visible event

		UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnDamageTaken OnDamageTaken; // blueprint visible event

		UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHealth(); // blueprint pure function used as getter for health

		UFUNCTION(BlueprintCallable, Category = "Health")
		void HealthPickedUp();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnDamageTaken();

private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Health")
	float Health; // current health variable
};
