// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff.h"
#include"BaseBuff.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
// Sets default values for this component's properties
UBuff::UBuff()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UBuff::BeginPlay()
{
	Super::BeginPlay();


	// ...
	
}


// Called every frame
void UBuff::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckAllBuff(DeltaTime);
	// ...
}

void UBuff::AddBuff(ABaseBuff * NewBuff)
{
	ABaseCharacter* OwnerPawn = Cast<ABaseCharacter>(GetOwner());
	if (OwnerPawn)
	{
		NewBuff->BuffIsEffective(OwnerPawn);
		AllBuff.Add(NewBuff);
	}
}

void UBuff::RemoveBuff(ABaseBuff * NewBuff)
{
	if (AllBuff.Contains(NewBuff))
	{
		ABaseCharacter* OwnerPawn = Cast<ABaseCharacter>(GetOwner());
		if (OwnerPawn)
		{
			NewBuff->EndBuff(OwnerPawn);
			NewBuff->Destroy();
		}
	}
}

void UBuff::CheckAllBuff(float DeltaTime)
{
	for (int32 i = 0; i < AllBuff.Num(); ++i)
	{
		if (AllBuff[i]->IsBuffEnd())
		{
			ABaseBuff* RemovedBuff = AllBuff[i];
			RemoveBuff(RemovedBuff);
		}
		AllBuff[i]->CurTime += DeltaTime;
	}
}

void UBuff::ClearAllBuff()
{
	for (int32 i = 0; i < AllBuff.Num(); ++i)
	{
		RemoveBuff(AllBuff[i]);
	}
}

