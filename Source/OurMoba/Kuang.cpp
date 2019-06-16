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

void AKuang::MulticastSkillEffects_Implementation(UParticleSystem* Particle, FVector EffectLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Particle, EffectLocation);
}

void AKuang::ServerSkill1Thunder_Implementation(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0)) return;
	if (!SkillComp->CheckCanBeReleased(0)) return;
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Skill1React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

bool AKuang::ServerSkill1Thunder_Validate(FVector Target)
{
	return true;
}

void AKuang::ServerSkill2LightDurance_Implementation(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(1)) return;
	if (!SkillComp->CheckCanBeReleased(1)) return;
	SkillComp->ReleaseSkill(1);
	MulticastSkillEffects(Skill2React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill2EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		ADurance* Durance = GetWorld()->SpawnActor<ADurance>(ADurance::StaticClass());
		Durance->SustainTime = 1.2 + SkillComp->GetSkillLevel(1)*0.2f;
		AllEnemysInRadius[i]->BuffComp->AddBuff(Durance);
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

bool AKuang::ServerSkill2LightDurance_Validate(FVector Target)
{
	return true;
}

void AKuang::ServerSkill3Frenzy_Implementation()
{
	if (!SkillComp->CheckCanBeReleased(2)) return;
	SkillComp->ReleaseSkill(2);
	ARage* Rage = GetWorld()->SpawnActor<ARage>(ARage::StaticClass());
	Rage->SustainTime = 7.0f + SkillComp->GetSkillLevel(2)*1.0f;
	Rage->DeltaAttackSpeed = (0.2 + SkillComp->GetSkillLevel(2)*0.05)*PropertyComp->GetCurAttackSpeed();
	Rage->DeltaPhyDamage = (0.2 + SkillComp->GetSkillLevel(2)*0.05)*PropertyComp->GetCurPhyAttack();
	BuffComp->AddBuff(Rage);
}

bool AKuang::ServerSkill3Frenzy_Validate()
{
	return true;
}

void AKuang::Skill1Thunder(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0)) return;
	if (!SkillComp->CheckCanBeReleased(0)) return;
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Skill1React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

void AKuang::Skill2LightDurance(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(1)) return;
	if (!SkillComp->CheckCanBeReleased(1)) return;
	SkillComp->ReleaseSkill(1);
	MulticastSkillEffects(Skill2React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill2EffectRange, Target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		ADurance* Durance = GetWorld()->SpawnActor<ADurance>(ADurance::StaticClass());
		Durance->SustainTime = 1.2 + SkillComp->GetSkillLevel(1)*0.2f;
		AllEnemysInRadius[i]->BuffComp->AddBuff(Durance);
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

void AKuang::Skill3Frenzy()
{
	if (!SkillComp->CheckCanBeReleased(2)) return;
	SkillComp->ReleaseSkill(2);
	ARage* Rage = GetWorld()->SpawnActor<ARage>(ARage::StaticClass());
	Rage->SustainTime = 7.0f + SkillComp->GetSkillLevel(2)*1.0f;
	Rage->DeltaAttackSpeed= (0.2 + SkillComp->GetSkillLevel(2)*0.05)*PropertyComp->GetCurAttackSpeed();
	Rage->DeltaPhyDamage= (0.2 + SkillComp->GetSkillLevel(2)*0.05)*PropertyComp->GetCurPhyAttack();
	BuffComp->AddBuff(Rage);
}

void AKuang::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	if (Role == ROLE_Authority)
	{
		Skill1Thunder(MouseLocation);
	}
	else if(Role < ROLE_Authority)
	{
		ServerSkill1Thunder(MouseLocation);
	}
}

void AKuang::Skill2Release()
{
	FVector MouseLocation = GetMouseLocation();
	if (Role == ROLE_Authority)
	{
		Skill2LightDurance(MouseLocation);
	}
	else if (Role < ROLE_Authority)
	{
		ServerSkill2LightDurance(MouseLocation);
	}
}

void AKuang::Skill3Release()
{
	if (Role == ROLE_Authority)
	{
		Skill3Frenzy();
	}
	else if (Role < ROLE_Authority)
	{
		ServerSkill3Frenzy();
	}
}
