// Fill out your copyright notice in the Description page of Project Settings.


#include "Shinbi.h"
#include"Skill.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include"Kismet\GameplayStatics.h"
#include"Particles\ParticleSystem.h"
#include"Components\SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include"Runtime/NavigationSystem/Public/NavigationSystem.h"
#include"Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include"Engine\World.h"
#include"CharacterProperty.h"
#include"GhostForm.h"
#include"Buff.h"
#include"DeathFlag.h"
void AShinbi::MulticastSkillEffects_Implementation(UParticleSystem* Particle, FVector EffectLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Particle, EffectLocation);
}

void AShinbi::ServerSkill1Blink_Implementation(FVector Target)
{
	FVector MyLocation = GetActorLocation();
	FVector Direction = Target - MyLocation;
	FNavLocation  RealPoint;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0)) return;
	if (!SkillComp->CheckCanBeReleased(0)) return;
	UNavigationSystemV1* NavigationSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSys)
	{
		if (NavigationSys->ProjectPointToNavigation(Target, RealPoint, FVector(500.0f, 500.0f, 500.0f)))
		{
			SkillComp->ReleaseSkill(0);
			MulticastSkillEffects(Skill1React, MyLocation);
			float Radius, Hight;
			GetCapsuleComponent()->GetScaledCapsuleSize(Radius, Hight);
			RealPoint.Location.Z += Hight;
			SetActorLocation(RealPoint.Location);
			float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
			TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, RealPoint.Location);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
			}
			AllEnemysInRadius.Empty();
			AllEnemysInRadius = GetAllEnemysInRadius(Skill1EffectRange);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
			}
			MulticastSkillEffects(Skill1React, RealPoint.Location);
		}
	}
}

bool AShinbi::ServerSkill1Blink_Validate(FVector Target)
{
	return true;
}

void AShinbi::Skill2BecomeGhost()
{
	SkillComp->ReleaseSkill(1);
	AGhostForm* GhostForm= GetWorld()->SpawnActor<AGhostForm>(AGhostForm::StaticClass());
	GhostForm->DeltaAttackSpeed = (0.1 + SkillComp->GetSkillLevel(1)*0.05)*PropertyComp->GetCurAttackSpeed();
	GhostForm->DeltaMoveSpeed = (0.2 + SkillComp->GetSkillLevel(1)*0.1)*PropertyComp->GetCurMoveSpeed();
	BuffComp->AddBuff(GhostForm);
}

void AShinbi::ServerSkill2BecomeGhost_Implementation()
{
	if (SkillComp->CheckCanBeReleased(1))
	{
		return;
	}
	SkillComp->ReleaseSkill(1);
	AGhostForm* GhostForm = GetWorld()->SpawnActor<AGhostForm>(AGhostForm::StaticClass());
	GhostForm->DeltaAttackSpeed = (0.1 + SkillComp->GetSkillLevel(1)*0.05)*PropertyComp->GetCurAttackSpeed();
	GhostForm->DeltaMoveSpeed = (0.2 + SkillComp->GetSkillLevel(1)*0.1)*PropertyComp->GetCurMoveSpeed();
	BuffComp->AddBuff(GhostForm);
}

bool AShinbi::ServerSkill2BecomeGhost_Validate()
{
	return true;
}

void AShinbi::ServerSkill3DeathTarget_Implementation(FVector target)
{

}

bool AShinbi::ServerSkill3DeathTarget_Validate(FVector target)
{
	return true;
}

void AShinbi::Skill3DeathTarget(FVector target)
{
	SkillComp->ReleaseSkill(2);
	UGameplayStatics::SpawnEmitterAtLocation(this, Skill3React, target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill3EffectRange, target);
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(2);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		if (AllEnemysInRadius[i]->PropertyComp->IsAlive())
		{
			ADeathFlag* DeathFlag = GetWorld()->SpawnActor<ADeathFlag>(ADeathFlag::StaticClass());
			DeathFlag->DeltaMoveSpeed = AllEnemysInRadius[i]->PropertyComp->GetCurMoveSpeed()*-0.8f;
			DeathFlag->DeltaPhyDef = AllEnemysInRadius[i]->PropertyComp->GetCurPhyDef()*-0.4f;
			DeathFlag->Attacker = this;
			AllEnemysInRadius[i]->BuffComp->AddBuff(DeathFlag);
			AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
		}
	}
}

void AShinbi::Skill1Blink(FVector Target)
{
	FVector MyLocation = GetActorLocation();
	FVector Direction = Target - MyLocation;
	FNavLocation  RealPoint;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0)) return;
	if (!SkillComp->CheckCanBeReleased(0)) return;
	UNavigationSystemV1* NavigationSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSys)
	{
		if (NavigationSys->ProjectPointToNavigation(Target, RealPoint, FVector(500.0f, 500.0f, 500.0f)))
		{
			SkillComp->ReleaseSkill(0);
			MulticastSkillEffects(Skill1React, MyLocation);
			float Radius, Hight;
			GetCapsuleComponent()->GetScaledCapsuleSize(Radius, Hight);
			RealPoint.Location.Z += Hight;
			SetActorLocation(RealPoint.Location);
			float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
			TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, RealPoint.Location);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
			}
			AllEnemysInRadius.Empty();
			AllEnemysInRadius = GetAllEnemysInRadius(Skill1EffectRange);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
			}
			MulticastSkillEffects(Skill1React, RealPoint.Location);
		}
	}
}

void AShinbi::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	if (Role == ROLE_Authority)
	{
		Skill1Blink(MouseLocation);
	}
	else
	{
		ServerSkill1Blink(MouseLocation);
	}
}

void AShinbi::Skill2Release()
{
	if (Role == ROLE_Authority)
	{
		Skill2BecomeGhost();
	}
	else if (Role < ROLE_Authority)
	{
		ServerSkill2BecomeGhost();
	}
}

void AShinbi::Skill3Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocation = GetActorLocation();
	FVector Direction = MouseLocation - MyLocation;
	Direction.Z = 0.0f;

	if (Direction.Size() < SkillComp->GetSkillRange(2))
	{
		if (SkillComp->CheckCanBeReleased(2))
		{
			Skill3DeathTarget(MouseLocation);
		}
	}
}
