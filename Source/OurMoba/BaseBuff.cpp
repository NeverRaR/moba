// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
// Sets default values
ABaseBuff::ABaseBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	React = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("React"));

	React->SetVisibility(false);

	React->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABaseBuff::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseBuff::IsBuffEnd()
{
	return CurTime >= SustainTime;
}

