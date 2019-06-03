// Fill out your copyright notice in the Description page of Project Settings.


#include "Kuang.h"
#include"Skill.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include"Kismet\GameplayStatics.h"
#include"Particles\ParticleSystem.h"
#include"CharacterProperty.h"
AKuang::AKuang()
{

	
}

void AKuang::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() <SkillComp->GetSkillRange(0))
	{
		if (PropertyComp->GetCurMP() > SkillComp->GetSkillMPConsume(0))
		{
			if (SkillComp->GetSkillCurCD(0) < 0.001&&SkillComp->GetSkillLevel(0) > 0)
			{
				SkillComp->ResetSkillCurCD(0);
				PropertyComp->AddCurMP(-1 * SkillComp->GetSkillMPConsume(0));
				UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, MouseLocation);
				TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, MouseLocation);
				for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
				{
					AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
				}
			}
		}
	}
}
