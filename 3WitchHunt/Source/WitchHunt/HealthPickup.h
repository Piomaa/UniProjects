// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDownCharacter.h"
#include "HealthPickup.generated.h"

UCLASS()
class WITCHHUNT_API AHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickup();


public:	
	/** Collectable static mesh */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	UStaticMeshComponent* StaticMesh;

	/** Allows child components to move freely */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	USceneComponent* DefaultSceneRoot;

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
