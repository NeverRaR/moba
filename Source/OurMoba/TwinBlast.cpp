// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinBlast.h"
#include"Animiation.h"
#include"Kismet/KismetMathLibrary.h"
#include"MobaController.h"
#include"CharacterProperty.h"
#include"Burning.h"
#include"Kismet\GameplayStatics.h"
#include"Particles\ParticleSystem.h"
#include"Buff.h"
#include"Components\SkeletalMeshComponent.h"
void ATwinBlast::OnSetAttackPressed()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < PropertyComp->GetAttackRange()) {
		if (bIsAttacking)
		{
			bIsReadyToCombo = true;
		}
		else
		{
			TurnToMouseLocation();
			bIsAttacking = true;
			if (Role < ROLE_Authority)
			{
				AttackTarget = MouseLocation;
				ServerSetAttackTarget(MouseLocation);
			}
			else
			{
				AttackTarget = MouseLocation;
			}
			PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, true);
		}
	}
}

void ATwinBlast::ServerSetAttackTarget_Implementation(FVector Target)
{
	AttackTarget = Target;
}

bool ATwinBlast::ServerSetAttackTarget_Validate(FVector Target)
{
	return true;
}

void ATwinBlast::CRoleComboAttack(int32 NextIndex)
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < PropertyComp->GetAttackRange()) {
		if (bIsReadyToCombo)
		{
			if (Role < ROLE_Authority)
			{
				AttackTarget = MouseLocation;
				ServerSetAttackTarget(MouseLocation);
			}
			else
			{
				AttackTarget = MouseLocation;
			}
			TurnToMouseLocation();
			bIsReadyToCombo = false;
			PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, PropertyComp->GetCurAttackSpeed());
		}
	}
}

void ATwinBlast::TurnToMouseLocation()
{

	FVector MouseLocaton = GetMouseLocation();
	FVector OwnerLocation = GetActorLocation();
	FVector DirLocation = GetMouseLocation() - GetActorLocation();
	if (DirLocation.Size())
	{
		DirLocation = TurnCoefficient *DirLocation / (DirLocation.Size());
	}
	AMobaController* MC = Cast<AMobaController>(Controller);
	if (MC)
	{
		MC->SetNewMoveDestination(DirLocation);
	}
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseLocaton).Yaw;
	if (Role == ROLE_Authority)
	{
		SetActorRotation(NewRotation);
	}
	else if (Role < ROLE_Authority)
	{
		ServerSetRotation(NewRotation);
	}
}

void ATwinBlast::ServerSetRotation_Implementation(FRotator Rotation)
{
	SetActorRotation(Rotation);
}

bool ATwinBlast::ServerSetRotation_Validate(FRotator Rotation)
{
	return true;
}

void ATwinBlast::MulticastSkillEffects_Implementation(UParticleSystem* Particle, FVector EffectLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Particle, EffectLocation);
}

void ATwinBlast::ServerSkill1Shrapnel_Implementation(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0)) return;
	if (!SkillComp->CheckCanBeReleased(0)) return;
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Skill1React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		ABurning* Burning = GetWorld()->SpawnActor<ABurning>(ABurning::StaticClass());
		Burning->DeltaMoveSpeed = AllEnemysInRadius[i]->PropertyComp->GetCurMoveSpeed()*-0.4f;
		Burning->Attacker = this;
		AllEnemysInRadius[i]->BuffComp->AddBuff(Burning);
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

bool ATwinBlast::ServerSkill1Shrapnel_Validate(FVector Target)
{
	return true;
}

void ATwinBlast::ServerSkill2SelfHeal_Implementation()
{

}

bool ATwinBlast::ServerSkill2SelfHeal_Validate()
{
	return true;
}

void ATwinBlast::Skill1Shrapnel(FVector Target)
{
	FVector MyLocaion = GetActorLocation();
	FVector Direction = Target - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() > SkillComp->GetSkillRange(0)) return;
	if (!SkillComp->CheckCanBeReleased(0)) return;
	float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
	SkillComp->ReleaseSkill(0);
	MulticastSkillEffects(Skill1React, Target);
	TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, Target);
	for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
	{
		ABurning* Burning = GetWorld()->SpawnActor<ABurning>(ABurning::StaticClass());
		Burning->DeltaMoveSpeed = AllEnemysInRadius[i]->PropertyComp->GetCurMoveSpeed()*-0.4f;
		Burning->Attacker = this;
		AllEnemysInRadius[i]->BuffComp->AddBuff(Burning);
		AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
	}
}

void ATwinBlast::Skill2SelfHeal()
{

}

void ATwinBlast::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	if (Role == ROLE_Authority)
	{
		Skill1Shrapnel(MouseLocation);
	}
	else if (Role < ROLE_Authority)
	{
		ServerSkill1Shrapnel(MouseLocation);
	}
}

void ATwinBlast::Skill2Release()
{
	if (SkillComp->CheckCanBeReleased(1))
	{
		SkillComp->ReleaseSkill(1);

		UGameplayStatics::SpawnEmitterAtLocation(this, Skill2React,GetActorLocation());
		if (PropertyComp->IsAlive())
		{
			PropertyComp->AddCurHP(SkillComp->GetSkillLevel(1) * 50 + 100);
			ABaseBuff* SpeedUp= GetWorld()->SpawnActor<ABaseBuff>(ABaseBuff::StaticClass());
			SpeedUp->SustainTime = 4.0f;
			SpeedUp->DeltaMoveSpeed =PropertyComp->GetCurMoveSpeed()*(0.3f+0.05f*SkillComp->GetSkillLevel(1));
			BuffComp->AddBuff(SpeedUp);
		}
	}
}