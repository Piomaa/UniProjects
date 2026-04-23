//Fireball spell class


#include "FireballSpell.h"
#include "GameFramework/ProjectileMovementComponent.h"

UFireballSpell::UFireballSpell()
{
	Name = "Fireball";
	ManaCost = 10.f;
	Cooldown = 0.5f;
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FireballEffectFinder(TEXT("/Game/FX/NS_FireballTest")); // setup the niagara effect file
    if (FireballEffectFinder.Succeeded())
    {
        FireballEffect = FireballEffectFinder.Object;
    }

    static ConstructorHelpers::FClassFinder<AActor> FireballBPFinder(TEXT("/Game/Blueprints/BP_Fireball")); // we handle collision events and more in blueprint
    if (FireballBPFinder.Succeeded())
    {
        FireballToSpawn = FireballBPFinder.Class;
    }
}

void UFireballSpell::CastSpell(FVector SpawnLocation, FVector Location)
{
    // Calculate the direction and velocity towards the target location
    FVector Direction = (Location - SpawnLocation).GetSafeNormal();
    float Speed = 1000.0f; // Set the desired speed for the fireball, this should be a class wide variable ideally
    FVector Velocity = Direction * Speed;

    // Spawn the Fireball Actor on the server
    AActor* Fireball = GetWorld()->SpawnActor<AActor>(FireballToSpawn, SpawnLocation, FRotator::ZeroRotator);
    if (Fireball)
    {
        UProjectileMovementComponent* ProjectileComp = Fireball->FindComponentByClass<UProjectileMovementComponent>();
        if (ProjectileComp)
        {
            ProjectileComp->Velocity = Direction * ProjectileComp->InitialSpeed;
        }
    }

    // Call the multicast function to spawn the Niagara effect on all clients
    Multicast_SpawnFireballEffect(SpawnLocation, Velocity); // this doesn't seem to work properly unfortunately, the client cannot see the host's fireballs

    LastCastTime = GetWorld()->GetTimeSeconds(); // reset cooldown time
}


void UFireballSpell::Multicast_SpawnFireballEffect_Implementation(FVector SpawnLocation, FVector Velocity)
{
    // Spawn the Niagara particle system at the specified location
    UNiagaraComponent* FireballNS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FireballEffect, SpawnLocation, FRotator::ZeroRotator);

    // Set the initial velocity parameter in the Niagara system
    if (FireballNS)
    {
        FireballNS->SetVectorParameter(FName("InitialVelocity"), Velocity); // give the effect the same velocity as the projectile
    }
}
