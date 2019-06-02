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
	AllBuff.Add(NewBuff);
	ABaseCharacter* OwnerPawn = Cast<ABaseCharacter>(GetOwner());
	if (OwnerPawn)
	{
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		MyProperty->AddCurMaxHP(NewBuff->DeltaMaxHP);
		MyProperty->AddCurMaxMP(NewBuff->DeltaMaxMP);
		MyProperty->AddCurHP(NewBuff->DeltaMaxHP);
		MyProperty->AddCurMP(NewBuff->DeltaMaxMP);
		MyProperty->AddCurMPRecovery(NewBuff->DeltaMPRecovery);
		MyProperty->AddCurHPRecovery(NewBuff->DeltaHPRecovery);
		MyProperty->AddCurPhyAttack(NewBuff->DeltaPhyDamage);
		MyProperty->AddCurMagAttack(NewBuff->DeltaMagDamage);
		MyProperty->AddCurPhyDef(NewBuff->DeltaPhyDef);
		MyProperty->AddCurMagDef(NewBuff->DeltaMagDef);
		MyProperty->AddCurAttackSpeed(NewBuff->DeltaAttackSpeed);
		MyProperty->AddCurMoveSpeed(NewBuff->DeltaMoveSpeed);
		NewBuff->React->SetVisibility(true);
	}
}

void UBuff::RemoveBuff(ABaseBuff * NewBuff)
{
	if (AllBuff.Contains(NewBuff))
	{
		ABaseCharacter* OwnerPawn = Cast<ABaseCharacter>(GetOwner());
		if (OwnerPawn)
		{
			UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
			MyProperty->AddCurMaxHP(-1*NewBuff->DeltaMaxHP);
			MyProperty->AddCurMaxMP(-1 * NewBuff->DeltaMaxMP);
			MyProperty->AddCurMPRecovery(-1 * NewBuff->DeltaMPRecovery);
			MyProperty->AddCurHPRecovery(-1 * NewBuff->DeltaHPRecovery);
			MyProperty->AddCurPhyAttack(-1 * NewBuff->DeltaPhyDamage);
			MyProperty->AddCurMagAttack(-1 * NewBuff->DeltaMagDamage);
			MyProperty->AddCurPhyDef(-1 * NewBuff->DeltaPhyDef);
			MyProperty->AddCurMagDef(-1 * NewBuff->DeltaMagDef);
			MyProperty->AddCurAttackSpeed(-1 * NewBuff->DeltaAttackSpeed);
			MyProperty->AddCurMoveSpeed(-1 * NewBuff->DeltaMoveSpeed);
		}
		AllBuff.Remove(NewBuff);
		NewBuff->React->SetVisibility(false);
		NewBuff->Destroy();
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

