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
			PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, true);
		}
	}
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
	SetActorRotation(NewRotation);
}

void ATwinBlast::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < SkillComp->GetSkillRange(0))
	{
		if (SkillComp->CheckCanBeReleased(0))
		{
			float Damage = PropertyComp->GetCurMagAttack() + SkillComp->GetSkillMagDamage(0);
			SkillComp->ReleaseSkill(0);
			UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, MouseLocation);
			TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, MouseLocation);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				ABurning* Burning = GetWorld()->SpawnActor<ABurning>(ABurning::StaticClass());
				Burning->DeltaMoveSpeed = AllEnemysInRadius[i]->PropertyComp->GetCurMoveSpeed()*-0.4f;
				Burning->Attacker = this;
				AllEnemysInRadius[i]->BuffComp->AddBuff(Burning);
				AllEnemysInRadius[i]->ReceiveMagDamage(Damage, this);
			}
		}
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