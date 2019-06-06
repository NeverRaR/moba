// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Net/UnrealNetwork.h"
// Sets default values

ABaseBuff::ABaseBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	React = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("React"));

	React->SetVisibility(false);

	React->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetReplicates(true);
	React->SetIsReplicated(true);
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
	if (Receiver)
	{
		if (React)
		{
			React->SetWorldLocation(Receiver->GetActorLocation());
			React->SetWorldRotation(Receiver->GetActorRotation());
		}
	}
}
void ABaseBuff::EnforceEndBuff()
{
	React->SetVisibility(false);
	Destroy();
}
bool ABaseBuff::IsBuffEnd()
{
	return CurTime >= SustainTime;
}
bool ABaseBuff::BuffIsEffective(ABaseCharacter* OwnerPawn)
{
	if (OwnerPawn)
	{
		Receiver = OwnerPawn;
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		MyProperty->AddCurMaxHP(DeltaMaxHP);
		MyProperty->AddCurMaxMP(DeltaMaxMP);
		MyProperty->AddCurHP(DeltaMaxHP);
		MyProperty->AddCurMP(DeltaMaxMP);
		MyProperty->AddCurMPRecovery(DeltaMPRecovery);
		MyProperty->AddCurHPRecovery(DeltaHPRecovery);
		MyProperty->AddCurPhyAttack(DeltaPhyDamage);
		MyProperty->AddCurMagAttack(DeltaMagDamage);
		MyProperty->AddCurPhyDef(DeltaPhyDef);
		MyProperty->AddCurMagDef(DeltaMagDef);
		MyProperty->AddCurAttackSpeed(DeltaAttackSpeed);
		MyProperty->AddCurMoveSpeed(DeltaMoveSpeed);
		MyProperty->AddCurLeech(DeltaLeech);
		MyProperty->AddCurCDReduction(DeltaCDReduction);
		React->SetVisibility(true);
		return true;
	}
	return false;
}

bool ABaseBuff::EndBuff(ABaseCharacter* OwnerPawn)
{
	if (OwnerPawn)
	{
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		MyProperty->AddCurMaxHP(-DeltaMaxHP);
		MyProperty->AddCurMaxMP(-DeltaMaxMP);
		MyProperty->AddCurMPRecovery(-DeltaMPRecovery);
		MyProperty->AddCurHPRecovery(-DeltaHPRecovery);
		MyProperty->AddCurPhyAttack(-DeltaPhyDamage);
		MyProperty->AddCurMagAttack(-DeltaMagDamage);
		MyProperty->AddCurPhyDef(-DeltaPhyDef);
		MyProperty->AddCurMagDef(-DeltaMagDef);
		MyProperty->AddCurAttackSpeed(-DeltaAttackSpeed);
		MyProperty->AddCurMoveSpeed(-DeltaMoveSpeed);
		MyProperty->AddCurLeech(-DeltaCDReduction);
		React->SetVisibility(false);
		return true;
	}
	return false;
}