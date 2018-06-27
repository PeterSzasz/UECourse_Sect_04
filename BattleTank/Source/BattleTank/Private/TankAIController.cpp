// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
	
	Super::BeginPlay();

	UE_LOG(LogTemp,Warning,TEXT("AI Controller"));

	auto TankPawn = GetControlledTank();
	if(TankPawn){
		UE_LOG(LogTemp,Warning,TEXT("Controlling: %s"),*TankPawn->GetActorLabel())
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetPlayerTank())
	{
		// Move towards player

		// Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank){
		return Cast<ATank>(PlayerTank);
	}

	return nullptr;
}


