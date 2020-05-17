// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay(); // makes sure that the BeginPlay is being called on Super

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) 
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s."), *(ControlledTank->GetName()));
    }    
}

ATank* ATankPlayerController::GetControlledTank() const
{
    // Return Pawn the player is currently possessing
    /* GetPawn returns a APawn* which means that it can only call functions of APawn 
    even if the controlled pawn is actually of type ATank. So Cast will treat that as ATank.*/
    return Cast<ATank>(GetPawn());
}