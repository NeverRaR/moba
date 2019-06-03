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
void AShinbi::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < SkillComp->GetSkillRange(0))
	{
		if (PropertyComp->GetCurMP() > SkillComp->GetSkillMPConsume(0))
		{
			if (SkillComp->GetSkillCurCD(0) < 0.001&&SkillComp->GetSkillLevel(0) > 0)
			{

				FNavLocation  RealPoint;
				UNavigationSystemV1* NavigationSys = UNavigationSystemV1::GetCurrent(GetWorld());
				if (NavigationSys)
				{
					if (NavigationSys->ProjectPointToNavigation(MouseLocation, RealPoint, FVector(500.0f, 500.0f, 500.0f)))
					{
						SkillComp->ResetSkillCurCD(0);
						PropertyComp->AddCurMP(-1 * SkillComp->GetSkillMPConsume(0));
						UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, MyLocaion);
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
						UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, RealPoint.Location);
					}
				}
			}
		}
	}
}
