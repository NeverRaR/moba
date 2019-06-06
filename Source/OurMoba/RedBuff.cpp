// Fill out your copyright notice in the Description page of Project Settings.


#include "RedBuff.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Burning.h"
#include"UObject/ConstructorHelpers.h"
#include"Particles\ParticleSystemComponent.h"
ARedBuff::ARedBuff()
{
	SustainTime = 70.0f;
	DeltaHPRecovery = 15.0f;
	bIsUnique = true;
	Type = BuffType::RedBuff;
	bIsDebuffInstigator = true;
	AttachedDebuff = NewObject<ABurning>();
	check(AttachedDebuff!=nullptr)
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemMaterialAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_Dragon_Spawn.P_Dragon_Spawn'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		React->Template = ParticleSystemMaterialAsset.Object;
		React->ActivateSystem(true);
	}
}

