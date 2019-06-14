// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEquipment.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
#include"BaseCharacter.h"
#include"Hero.h"
#include"CharacterProperty.h"
#include"Net/UnrealNetwork.h"
// Sets default values

ABaseEquipment::ABaseEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseEquipment::EquipmentIsEffective(AHero* OwnerPawn)
{
	if (OwnerPawn)
	{
		Receiver = OwnerPawn;
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		MyProperty->AddMoney(-NeedGold);
		MyProperty->AddBaseMaxHP(DeltaMaxHP);
		MyProperty->AddBaseMaxMP(DeltaMaxMP);
		MyProperty->AddBaseHPRecovery(DeltaHPRecovery);
		MyProperty->AddBaseMPRecovery(DeltaMPRecovery);
		MyProperty->AddBasePhyAttack(DeltaPhyDamage);
		MyProperty->AddBaseMagAttack(DeltaMagDamage);
		MyProperty->AddBasePhyDef(DeltaPhyDef);
		MyProperty->AddBaseMagDef(DeltaMagDef);
		MyProperty->AddBaseAttackSpeed(DeltaAttackSpeed);
		MyProperty->AddBaseMoveSpeed(DeltaMoveSpeed);
		MyProperty->AddBaseLeech(DeltaLeech);
		MyProperty->AddBaseCDReduction(DeltaCDReduction);
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
		return true;
	}
	return false;
}

bool ABaseEquipment::EndEquipment(AHero* OwnerPawn)
{
	if (OwnerPawn)
	{
		Receiver = OwnerPawn;
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		MyProperty->AddMoney(0.6 * NeedGold);

		MyProperty->AddBaseMaxHP(-DeltaMaxHP);
		MyProperty->AddBaseMaxMP(-DeltaMaxMP);
		MyProperty->AddBaseHPRecovery(-DeltaHPRecovery);
		MyProperty->AddBaseMPRecovery(-DeltaMPRecovery);
		MyProperty->AddBasePhyAttack(-DeltaPhyDamage);
		MyProperty->AddBaseMagAttack(-DeltaMagDamage);
		MyProperty->AddBasePhyDef(-DeltaPhyDef);
		MyProperty->AddBaseMagDef(-DeltaMagDef);
		MyProperty->AddBaseAttackSpeed(-DeltaAttackSpeed);
		MyProperty->AddBaseMoveSpeed(-DeltaMoveSpeed);
		MyProperty->AddBaseLeech(-DeltaLeech);
		MyProperty->AddBaseCDReduction(-DeltaCDReduction);

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
		MyProperty->AddCurLeech(-DeltaLeech);
		MyProperty->AddCurCDReduction(-DeltaCDReduction);
		return true;
	}
	return false;
}

