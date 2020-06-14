// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // makes sure that the BeginPlay is being called on Super
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Return Pawn the player is currently possessing
	/* GetPawn returns a APawn* which means that it can only call functions of APawn
	even if the controlled pawn is actually of type ATank. So Cast will treat that as ATank.*/
	auto AIControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// TODO Move towards player

		// Aim towards player
		AIControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		AIControlledTank->Fire(); // TODO limit firing rate
	}
}
