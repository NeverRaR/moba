// Fill out your copyright notice in the Description page of Project Settings.


#include "Durance.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystemComponent.h"
#include"UObject/ConstructorHelpers.h"
ADurance::ADurance()
{
	SustainTime = 3.0f;
	bIsUnique = true;
	Type = BuffType::Durance;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemMaterialAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_KwangBuff.P_KwangBuff'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		React->Template = ParticleSystemMaterialAsset.Object;
	}
}
bool ADurance::BuffIsEffective(ABaseCharacter * OwnerPawn)
{
	if (OwnerPawn)
	{
		Receiver = OwnerPawn;
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		DeltaPhyDamage = -0.8* MyProperty->GetCurPhyAttack();
		DeltaMagDamage = -0.8*MyProperty->GetCurMagAttack();
		DeltaMoveSpeed = -1 * MyProperty->GetCurMoveSpeed();
		MyProperty->AddCurPhyAttack(DeltaPhyDamage);
		MyProperty->AddCurMagAttack(DeltaMagDamage);
		MyProperty->AddCurMoveSpeed(DeltaMoveSpeed);
		React->SetVisibility(true);
		return true;
	}
	return false;
}
