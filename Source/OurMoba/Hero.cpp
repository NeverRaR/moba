// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero.h"
#include"GameFramework\Actor.h"
#include "GameFramework/Controller.h"
#include"Skill.h"
#include "MobaController.h"
#include"CharacterProperty.h"
AHero::AHero()
{
	SkillComp = CreateDefaultSubobject<USkill>(TEXT("SkillComp"));
	
	CampComp->SetGroup(CharacterGroup::Hero);
}
void AHero::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Skill1Upgrade", IE_Pressed, this, &AHero::Skill1Upgrade);

	InputComponent->BindAction("Skill2Upgrade", IE_Pressed, this, &AHero::Skill2Upgrade);

	InputComponent->BindAction("Skill3Upgrade", IE_Pressed, this, &AHero::Skill3Upgrade);

	InputComponent->BindAction("Skill1Release", IE_Pressed, this, &AHero::Skill1Release);

	InputComponent->BindAction("Skill2Release", IE_Pressed, this, &AHero::Skill2Release);

	InputComponent->BindAction("Skill3Release", IE_Pressed, this, &AHero::Skill3Release);
}

void AHero::Skill1Upgrade()
{
	if (SkillComp->GetSkillPoint() > 0)
	{
		SkillComp->SkillLevelUp(0);
	}
}

void AHero::Skill2Upgrade()
{
	if (SkillComp->GetSkillPoint() > 0)
	{
		SkillComp->SkillLevelUp(1);
	}
}
void AHero::Skill3Upgrade()
{
	if (SkillComp->GetSkillPoint() > 0)
	{
		SkillComp->SkillLevelUp(2);
	}
}

void AHero::Skill1Release()
{
	if (SkillComp->GetSkillCurCD(0) < 0.001&&SkillComp->GetSkillLevel(0)>0)
	{
		SkillComp->ResetSkillCurCD(0);
	}
}

void AHero::Skill2Release()
{

	if (SkillComp->GetSkillCurCD(1) < 0.001&&SkillComp->GetSkillLevel(1) > 0)
	{
		SkillComp->ResetSkillCurCD(1);
	}
}

void AHero::Skill3Release()
{
	if (SkillComp->GetSkillCurCD(2) < 0.001&&SkillComp->GetSkillLevel(2) > 0)
	{
		SkillComp->ResetSkillCurCD(2);
	}
}
FVector AHero::GetMouseLocation()
{
	AMobaController* MC = Cast<AMobaController>(GetController());
	FHitResult Hit;
	if (MC)
	{
		MC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			return Hit.ImpactPoint;
		}
		return FVector(0, 0, 0);
	}
	return FVector(0, 0, 0);
}


void AHero::PhyDamageEnemy(TArray<ABaseCharacter*> Arr)
{
	float Damage = PropertyComp->GetCurPhyAttack();
	for (int32 i = 0; i < Arr.Num(); ++i)
	{
		ABaseCharacter* Receiver = Arr[i];
		AttackEffect(Receiver);
		float CurDamage = Receiver->ReceivePhyDamage(Damage, this);
		if (PropertyComp->IsAlive())
		{
			PropertyComp->AddCurHP(PropertyComp->GetCurLeech()*CurDamage);
		}
	}
}
