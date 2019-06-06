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

void AKuang::MulticastSkillEffects_Implementation(FVector EffectLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, EffectLocation);
}

void AKuang::ServerSkillThunder_Implementation(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0))
	{
		return;
	}
	if (PropertyComp->GetCurMP() < SkillComp->GetSkillMPConsume(0))
	{
		return;
	}
	if (SkillComp->GetSkillCurCD(0) > 0.001 || SkillComp->GetSkillLevel(0) <= 0)
	{
		return;
	}
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
	}
}

bool AKuang::ServerSkillThunder_Validate(FVector Target)
{
	return true;
}

void AKuang::SkillThunder(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0))
	{
		return;
	}
	if (PropertyComp->GetCurMP() < SkillComp->GetSkillMPConsume(0))
	{
		return;
	}
	if (SkillComp->GetSkillCurCD(0) > 0.001 || SkillComp->GetSkillLevel(0) <= 0)
	{
		return;
	}
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
	}
}

void AKuang::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Role == ROLE_Authority)
	{
		SkillThunder(MouseLocation);
	}
	else
	{
		ServerSkillThunder(MouseLocation);
	}
}
