// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override; //Virtual here means nothing but in a higher up inheritance, adding virtual allows the method to be accessed or overridden by it's children

	ATank* GetControlledTank() const;

	

private:
	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects with the world
	void AimTowardsCrosshair(); 
	// Returns an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const; //Return an OUT parameter, true if it hits landscape

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = .5f;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = .33333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


};
