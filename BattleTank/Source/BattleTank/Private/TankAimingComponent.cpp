// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UTankAimingComponent::Aiming(FVector HitLocation, float LaunchSpeed)
{
	if (Barrel)
	{
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation("Projectile");
		bool ValidTarget = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		if(ValidTarget)
		{
			MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// calc difference between aimdirect and current barrel rotation
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	auto OurTankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(5);	// TODO Remove magic number
}

