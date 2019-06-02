// Fill out your copyright notice in the Description page of Project Settings.


#include "Shinbi.h"
#include"Skill.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include"Kismet\GameplayStatics.h"
#include"Particles\ParticleSystem.h"
void AShinbi::Skill1Release()
{
	FVector MouseLocation = GetMouseLocation();
	FVector MyLocaion = GetActorLocation();
	FVector Direction = MouseLocation - MyLocaion;
	Direction.Z = 0.0f;
	if (Direction.Size() < SkillComp->GetSkillRange(0))
	{
		if (SkillComp->GetSkillCurCD(0) < 0.001&&SkillComp->GetSkillLevel(0) > 0)
		{
			SkillComp->ResetSkillCurCD(0);
			UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, MyLocaion);
			SetActorLocation(MouseLocation);
			UGameplayStatics::SpawnEmitterAtLocation(this, Skill1React, MouseLocation);
		}
	}
}