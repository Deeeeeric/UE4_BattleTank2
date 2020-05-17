// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay(); // makes sure that the BeginPlay is being called on Super

    auto AIControlledTank = GetAIControlledTank();
    if (!AIControlledTank) 
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not posessing a tank."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s."), *(AIControlledTank->GetName()));
    }    
}

ATank* ATankAIController::GetAIControlledTank() const
{
    // Return Pawn the player is currently possessing
    /* GetPawn returns a APawn* which means that it can only call functions of APawn 
    even if the controlled pawn is actually of type ATank. So Cast will treat that as ATank.*/
    return Cast<ATank>(GetPawn());
}