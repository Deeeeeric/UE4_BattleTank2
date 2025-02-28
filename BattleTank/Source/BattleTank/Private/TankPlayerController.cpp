// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
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

ATank *ATankPlayerController::GetControlledTank() const
{
    // Return Pawn the player is currently possessing
    /* GetPawn returns a APawn* which means that it can only call functions of APawn 
    even if the controlled pawn is actually of type ATank. So Cast will treat that as ATank.*/
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())
    {
        return;
    }

    FVector HitLocation; // Out paramter
    if (GetSightRayHitLocation(HitLocation)) // Has 'side-effect', going to line trace
    {
        GetControlledTank()->AimAt(HitLocation);
        //Get world location of linetrace through crosshair
        //if it hits the landscape
        // TODO tell the controlled tank to aim at this point
    }
}

// Get the location of landscape where the crosshair is aimed at, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
    // find the corsshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // line-trace along that LookDirection, and see what we hit (up to max range)
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
     // de-project the screen position of the crosshair to a world direction
    FVector CameraWorldLocation;

    return DeprojectScreenPositionToWorld
    (
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel
    (
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility
    ))
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false; // Line trace didnt succeed
}