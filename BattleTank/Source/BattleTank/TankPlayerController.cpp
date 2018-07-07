// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp,Warning,TEXT("Player Controller of The Tank"));

	auto TankPawn = GetControlledTank();
	/*if (TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got the Tank: %s"), *GetPawn()->GetActorLabel());
	}
	*/
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if(GetControlledTank())
	{
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation))
		{
			GetControlledTank()->AimAt(HitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)
{
	int ViewPortX;
	int ViewPortY;
	GetViewportSize(ViewPortX,ViewPortY);
	FVector2D ScreenLocation = FVector2D(ViewPortX * CrossHairXLocation, ViewPortY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{		
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)
{
	struct FHitResult OutHit;
	FVector StartVec = PlayerCameraManager->GetCameraLocation();
	if(GetWorld()->LineTraceSingleByChannel(OutHit, StartVec, StartVec+(LookDirection*LineTraceRange),ECC_Visibility))
	{
		HitLocation = OutHit.ImpactPoint;
		return true;
	}
	return false;
}