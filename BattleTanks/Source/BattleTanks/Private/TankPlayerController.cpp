// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h" 


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //Super says call the default behavior before anything else.

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not possessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing: %s"), *(ControlledTank->GetName())); //The "*" gets the contents of the location here. You get the location and * gets the contents
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector OutHitLocation; //Out parameter
	if (GetSightRayHitLocation(OutHitLocation)) //Has Side-effect which is going to the sightrayhit. The reference to the FVector& for OutHit allows the OutHitLocation to be referencing the OutHit 
	{
		GetControlledTank()->AimAt(OutHitLocation);
			// TODO Tell controlled tank to aim at the point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHit) const //Fvector& OutHit is a reference to the OutHitLocation above
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//Finds the crosshair location in terms of your own screensize
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along the look direction and see what he hit up to a max range
		GetLookVectorHitLocation(LookDirection, OutHit);
		
	}


	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)//Tells us to hit anything that is visible
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false; //Line trace didn't succeed
}



bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const //The stuff in the parenthesis is the stuff you plug into this function. They both derive from the function above
{
	//De-project the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;//To be discarded

	return	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}



