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
void AShinbi::MulticastSkillEffects_Implementation(FVector EffectLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, EffectLocation);
}

void AShinbi::ServerSkillBlink_Implementation(FVector Target)
{
	FVector MyLocation = GetActorLocation();
	FVector Direction = Target - MyLocation;
	FNavLocation  RealPoint;
	Direction.Z = 0.0f;
	UNavigationSystemV1* NavigationSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSys)
	{
		if (NavigationSys->ProjectPointToNavigation(Target, RealPoint, FVector(500.0f, 500.0f, 500.0f)))
		{
			SkillComp->ReleaseSkill(0);
			MulticastSkillEffects(MyLocation);
			float Radius, Hight;
			GetCapsuleComponent()->GetScaledCapsuleSize(Radius, Hight);
			RealPoint.Location.Z += Hight;
			SetActorLocation(RealPoint.Location);
			TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, RealPoint.Location);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
			}
			AllEnemysInRadius.Empty();
			AllEnemysInRadius = GetAllEnemysInRadius(Skill1EffectRange);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
			}
			MulticastSkillEffects(RealPoint.Location);
		}
	}
}

bool AShinbi::ServerSkillBlink_Validate(FVector Target)
{
	return true;
}

void AShinbi::SkillBlink(FVector Target)
{
	FVector MyLocation = GetActorLocation();
	FVector Direction = Target - MyLocation;
	FNavLocation  RealPoint;
	Direction.Z = 0.0f;
	UNavigationSystemV1* NavigationSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSys)
	{
		if (NavigationSys->ProjectPointToNavigation(Target, RealPoint, FVector(500.0f, 500.0f, 500.0f)))
		{
			SkillComp->ReleaseSkill(0);
			MulticastSkillEffects(MyLocation);
			float Radius, Hight;
			GetCapsuleComponent()->GetScaledCapsuleSize(Radius, Hight);
			RealPoint.Location.Z += Hight;
			SetActorLocation(RealPoint.Location);
			TArray<ABaseCharacter*> AllEnemysInRadius = GetAllEnemysInRadiusToLocation(Skill1EffectRange, RealPoint.Location);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
			}
			AllEnemysInRadius.Empty();
			AllEnemysInRadius = GetAllEnemysInRadius(Skill1EffectRange);
			for (int32 i = 0; i < AllEnemysInRadius.Num(); ++i)
			{
				AllEnemysInRadius[i]->ReceiveMagDamage(SkillComp->GetSkillMagDamage(0), this);
			}
			MulticastSkillEffects(RealPoint.Location);
		}
	}
}

void AShinbi::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocation = GetActorLocation();
	FVector Direction = MouseLocation - MyLocation;
	Direction.Z = 0.0f;

	if (Direction.Size() < SkillComp->GetSkillRange(0))
	{
		if (SkillComp->CheckCanBeReleased(0))
		{
			if (Role == ROLE_Authority)
			{
				SkillBlink(MouseLocation);
			}
			else
			{
				ServerSkillBlink(MouseLocation);
			}
		}
	}
}
