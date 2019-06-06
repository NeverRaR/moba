// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueBuff.h"
#include"UObject/ConstructorHelpers.h"
#include"Particles\ParticleSystemComponent.h"
ABlueBuff::ABlueBuff()
{
	SustainTime = 70.0f;
	DeltaMPRecovery = 15.0f;
	DeltaCDReduction = 0.2f;
	bIsUnique = true;
	Type = BuffType::BlueBuff;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemMaterialAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_Mudang_AttackWolves_CastLoop.P_Mudang_AttackWolves_CastLoop'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		React->Template = ParticleSystemMaterialAsset.Object;
	}
}