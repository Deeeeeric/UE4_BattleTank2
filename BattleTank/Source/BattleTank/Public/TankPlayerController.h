// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	ATank* GetControlledTank() const;

	// 'override' tells us to make sure there is something else in the inheritance tree with this signature
	virtual void BeginPlay() override; 

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	private:
	
	// Start the tank moving the barrel so that the shot would hit
	// where the crosshait intersects
	void AimTowardsCrosshair();

	// Get the location of the landscape the crosshair is aimed at
	// and consistently update the location if crosshair intersects with landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
