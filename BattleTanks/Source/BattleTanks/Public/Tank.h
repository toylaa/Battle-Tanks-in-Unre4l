// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"



class UTankBarrel;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this pawn's properties
	ATank();

	// AimAt() location
	void AimAt(FVector HitLocation);

	//make SetBarrelReference() available to blueprint
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	//Make Launch Speed of projectile accessible and overridable from blueprint
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000; //TODO find sensible starting value 

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:		
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
