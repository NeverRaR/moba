// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Minion.h"

// Sets default values
ABase_Minion::ABase_Minion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Minion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Minion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_Minion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

