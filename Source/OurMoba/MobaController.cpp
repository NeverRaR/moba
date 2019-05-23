// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "BaseCharacter.h"
#include "Engine/World.h"
AMobaController::AMobaController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
void AMobaController::BeginPlay()
{
	Super::BeginPlay();
}
void AMobaController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (bMoveToMouseCursor)
	{
			MoveToMouseCursor();
	}
}
void AMobaController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobaController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMobaController::OnSetDestinationReleased);
}
void AMobaController::MoveToMouseCursor()
{
	    ABaseCharacter* BaswOwner = Cast<ABaseCharacter>(GetOwner()); 
			// Trace to see what is under the mouse cursor
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);
			if (Hit.bBlockingHit)
			{
				// We hit something, move there
				SetNewMoveDestination(Hit.ImpactPoint);
			}
}
void AMobaController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		CMoveToLocation(this, DestLocation);
	}
}
void AMobaController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMobaController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
