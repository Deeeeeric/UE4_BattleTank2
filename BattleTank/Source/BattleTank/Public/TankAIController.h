// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	ATank *GetAIControlledTank() const;
	
	ATank *GetPlayerTank() const;

	// 'override' tells us to make sure there is something else in the inheritance tree with this signature
	virtual void BeginPlay() override;
};
