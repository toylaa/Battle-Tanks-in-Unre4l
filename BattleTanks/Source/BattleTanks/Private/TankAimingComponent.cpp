// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "Tank.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) 
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;

	//FVector StartLocation = 
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	
	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity
		(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
	);

	if (bHaveAimSolution )
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto TankName = GetOwner()->GetName();

		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	
	}

	//If no solution do nothing	

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Resolve difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	
	Barrel->ElevateBarrel(5); // TODO remove maagic number
}