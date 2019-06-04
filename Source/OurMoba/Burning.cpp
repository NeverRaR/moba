// Fill out your copyright notice in the Description page of Project Settings.


#include "Burning.h"
#include"UObject/ConstructorHelpers.h"
#include"Particles\ParticleSystemComponent.h"
ABurning::ABurning()
{
	SustainTime = 4.0f;
	DeltaHPRecovery = -15.0f;
	DeltaMoveSpeed = -200.0f;
	bIsUnique = true;
	Type = BuffType::Burning;
	bIsDebuffInstigator = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemMaterialAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_SentryTurret_Destroyed_Ruin.P_SentryTurret_Destroyed_Ruin'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		React->Template = ParticleSystemMaterialAsset.Object;
	}
}