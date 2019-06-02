// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "BaseCharacter.h"
#include"CharacterProperty.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Controller.h"
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
}
void AMobaController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobaController::OnSetDestinationPressed);
}
void AMobaController::MoveToMouseCursor()
{
			// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
}
void AMobaController::SetNewMoveDestination(FVector DestLocation)
{
	ABaseCharacter* MyPawn = Cast<ABaseCharacter>(GetPawn());
	if (MyPawn)
	{
		if (!MyPawn->PropertyComp->IsAlive()) DestLocation = MyPawn->GetActorLocation();
		AController* MovePC = Cast<AController>(this);
		CMoveToLocation(MovePC, DestLocation);
	}
}
void AMobaController::OnSetDestinationPressed()
{
	MoveToMouseCursor();
}

void AMobaController::CMoveToLocation_Implementation(AController * PC, const FVector & DestLocation)
{
	if (Role < ROLE_Authority)
	{
		return;
	}
	if (PC)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, DestLocation);
	}
}

bool AMobaController::CMoveToLocation_Validate(AController * PC, const FVector & DestLocation)
{
	return true;
}
