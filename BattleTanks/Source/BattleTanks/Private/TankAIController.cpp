// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h" 

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); //Super says call the default behavior before anything else.

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not aiming!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Aiming At: %s"), *(PlayerTank->GetName())); //The "*" gets the contents of the location here. You get the location and * gets the contents
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}


ATank* ATankAIController::GetControlledAi() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerTank);///They change this later so keep an eye on it
}


