// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay(); // makes sure that the BeginPlay is being called on Super

    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) 
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController can not find player tank."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController has found player: %s."), *(PlayerTank->GetName()));
    }    
}

ATank* ATankAIController::GetAIControlledTank() const
{
    // Return Pawn the player is currently possessing
    /* GetPawn returns a APawn* which means that it can only call functions of APawn 
    even if the controlled pawn is actually of type ATank. So Cast will treat that as ATank.*/
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) {return nullptr;}

    return Cast<ATank>(PlayerPawn);
}