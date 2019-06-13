// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include"BaseEquipment.h"
#include"Hero.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
// Sets default values for this component's properties
UEquipment::UEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipment::AddEquipment(ABaseEquipment*NewEquipment)
{
	AHero* OwnerPawn = Cast<AHero>(GetOwner());
	check(OwnerPawn)
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerAddEquipmentToClient(NewEquipment, OwnerPawn);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		AddEquipmentToServer(NewEquipment, OwnerPawn);
	}
}

void UEquipment::ServerAddEquipmentToClient_Implementation(ABaseEquipment * NewEquipment, AHero* TargetPawn)
{
	if (TargetPawn)
	{
		if (NewEquipment && AllEquipment.Num() < MaxEquipment)//不会超出最大装备数量
		{
			if (TargetPawn->PropertyComp->GetCurMoney() >= NewEquipment->NeedGold)
			{
				NewEquipment->EquipmentIsEffective(TargetPawn); //添加进去
				AllEquipment.Add(NewEquipment);
				TargetPawn->PropertyComp->AddMoney(-1 * NewEquipment->NeedGold);
			}
		}
	}
}

bool UEquipment::ServerAddEquipmentToClient_Validate(ABaseEquipment * NewEquipment, AHero* TargetPawn)
{
	return true;
}

void UEquipment::AddEquipmentToServer(ABaseEquipment * NewEquipment, AHero * TargetPawn)
{
	if (TargetPawn)
	{
		if (AllEquipment.Num() < MaxEquipment)//不会超出最大装备数量
		{
			if (TargetPawn->PropertyComp->GetCurMoney() >= NewEquipment->NeedGold)
			{
				NewEquipment->EquipmentIsEffective(TargetPawn); //添加进去
				AllEquipment.Add(NewEquipment);
				TargetPawn->PropertyComp->AddMoney(-1 * NewEquipment->NeedGold);
			}
		}
	}
}

void UEquipment::RemoveEquipment(ABaseEquipment*NewEquipment)
{
	AHero* OwnerPawn = Cast<AHero>(GetOwner());
	if (OwnerPawn&&NewEquipment)
	{
		NewEquipment->EndEquipment(OwnerPawn);
		AllEquipment.Remove(NewEquipment);
		OwnerPawn->PropertyComp->AddMoney(NewEquipment->NeedGold*0.3);
		NewEquipment->Destroy();
	}

}

void UEquipment::RemoveEquipmentFromServer(ABaseEquipment * NewEquipment, AHero * TargetPawn)
{
}

void UEquipment::ServerRemoveEquipmentFromClient_Implementation(ABaseEquipment * NewEquipment, AHero* TargetPawn)
{
	RemoveEquipment(NewEquipment);
}

bool UEquipment::ServerRemoveEquipmentFromClient_Validate(ABaseEquipment * NewEquipment, AHero* TargetPawn)
{
	return true;
}