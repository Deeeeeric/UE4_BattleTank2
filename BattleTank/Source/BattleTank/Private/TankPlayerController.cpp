// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

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

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
    
    // UE_LOG(LogTemp, Warning, TEXT("Player controller Tick")); debug
}

ATank* ATankPlayerController::GetControlledTank() const
{
    // Return Pawn the player is currently possessing
    /* GetPawn returns a APawn* which means that it can only call functions of APawn 
    even if the controlled pawn is actually of type ATank. So Cast will treat that as ATank.*/
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) {return;}

    OUT FVector HitLocation; // Out paramter
    if (GetSightRayHitLocation(HitLocation)) // Has 'side-effect', going to line trace
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit Location is: %s "), *HitLocation.ToString());

        //Get world location of linetrace through crosshair
        //if it hits the landscape
        // TODO tell the controlled tank to aim at this point
    }
    
}

 // Get the location of landscape where the crosshair is aimed at, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    HitLocation = FVector(1.0);
    return true; // 
}