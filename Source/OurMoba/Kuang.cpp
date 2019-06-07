// Fill out your copyright notice in the Description page of Project Settings.


#include "Kuang.h"
#include"Skill.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include"Kismet\GameplayStatics.h"
#include"Particles\ParticleSystem.h"
#include"CharacterProperty.h"
#include"Durance.h"
#include"Buff.h"
#include"Rage.h"
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
	if (!SkillComp->CheckCanBeReleased(0)) return;
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
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
	if (!SkillComp->CheckCanBeReleased(0)) return;
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

void AKuang::SkillLightDurance(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	SkillComp->ReleaseSkill(1);
	UGameplayStatics::SpawnEmitterAtLocation(this, Skill2React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill2EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		ADurance* Durance = GetWorld()->SpawnActor<ADurance>(ADurance::StaticClass());
		Durance->SustainTime = 1.5 + SkillComp->GetSkillLevel(1)*0.25f;
		AllEnemysInRadius[i]->BuffComp->AddBuff(Durance);
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

void AKuang::SkillFrenzy()
{
	SkillComp->ReleaseSkill(2);
	ARage* Rage = GetWorld()->SpawnActor<ARage>(ARage::StaticClass());
	Rage->SustainTime = 7.0f + SkillComp->GetSkillLevel(2)*2.0f;
	Rage->DeltaAttackSpeed= (0.1 + SkillComp->GetSkillLevel(2)*0.05)*PropertyComp->GetCurAttackSpeed();
	Rage->DeltaPhyDamage= (0.1 + SkillComp->GetSkillLevel(2)*0.05)*PropertyComp->GetCurPhyAttack();
	BuffComp->AddBuff(Rage);
}

void AKuang::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < SkillComp->GetSkillRange(0))
	{
		if (Role == ROLE_Authority)
		{
			SkillThunder(MouseLocation);
		}
		else
		{
			ServerSkillThunder(MouseLocation);
		}
	}
}

void AKuang::Skill2Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < SkillComp->GetSkillRange(1))
	{
		if (SkillComp->CheckCanBeReleased(1))
		{
			SkillLightDurance(MouseLocation);
		}
	}
}

void AKuang::Skill3Release()
{
		if (SkillComp->CheckCanBeReleased(2))
		{
			SkillFrenzy();
		}
}
