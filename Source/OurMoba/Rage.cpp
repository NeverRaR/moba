// Fill out your copyright notice in the Description page of Project Settings.


#include "Rage.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystemComponent.h"
#include"UObject/ConstructorHelpers.h"
ARage::ARage()
{
	SustainTime = 8.0f;
	bIsUnique = true;
	Type = BuffType::GhostForm;
	DeltaLeech = 0.8f;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemMaterialAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_Attack_Wolves_Trails.P_Attack_Wolves_Trails'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		React->Template = ParticleSystemMaterialAsset.Object;
	}
}
