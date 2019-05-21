// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MobaController.generated.h"
/**
 * 
 */
UCLASS()
class OURMOBA_API AMobaController : public APlayerController
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMobaController();
	void SetNewMoveDestination(const FVector DestLocation);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the given world location. */
	

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	UFUNCTION(BlueprintImplementableEvent)
		void CMoveToLocation(const APlayerController* PC,const FVector& DestLocation);
};