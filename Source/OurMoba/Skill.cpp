// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include"OurMobaGameMode.h"
#include"Hero.h"
#include "CharacterProperty.h"
#include "Net/UnrealNetwork.h"
// Sets default values for this component's properties
USkill::USkill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SkillPoint = 1;
	// ...
}


// Called when the game starts
void USkill::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void USkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	SkillWholeColdDown(DeltaTime);
}

int32 USkill::GetSkillLevel(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].SkillLevel;
	}
	return -1;
}

int32 USkill::GetMaxSkillLevel(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MaxSkillLevel;
	}
	return -1;
}


int32 USkill::SetSkillLevel(int32 id, int32 NewLevel)
{
	if (CheckIDIsLegal(id)&&NewLevel>0)
	{
		return SkillState[id].SkillLevel=NewLevel;
	}
	return -1;
}

int32 USkill::AddSkillLevel(int32 id, int32 DeltaLevel)
{
	if (CheckIDIsLegal(id) && DeltaLevel > 0)
	{
		return SkillState[id].SkillLevel += DeltaLevel;
	}
	return -1;
}

float USkill::GetSkillMagDamage(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MagDamage;
	}
	return -1.0f;
}

float USkill::SetSkillMagDamage(int32 id, float NewMagDamage)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MagDamage= NewMagDamage;
	}
	return -1.0f;
}

float USkill::AddSkillMagDamage(int32 id, float DeltaMagDamage)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MagDamage += DeltaMagDamage;
	}
	return -1.0f;
}

float USkill::GetSkillMagDamageGrowth(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MagDamageGrowth;
	}
	return -1.0f;
}

float USkill::GetSkillMPConsume(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MPConsume;
	}
	return -1.0f;
}

float USkill::SetSkillMPConsume(int32 id, float NewMPConsume)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MPConsume = NewMPConsume;
	}
	return -1.0f;
}

float USkill::AddSkillMPConsume(int32 id, float DeltaMPConsume)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MPConsume += DeltaMPConsume;
	}
	return -1.0f;
}

float USkill::GetSkillMPConsumeGrowth(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].MPConsumeGrowth;
	}
	return -1.0f;
}


float USkill::GetSkillCD(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].SkillCD;
	}
	return -1.0f;
}

float USkill::SetSkillCD(int32 id, float NewCD)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].SkillCD = NewCD;
	}
	return -1.0f;
}

float USkill::AddSkillCD(int32 id, float DeltaCD)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].SkillCD += DeltaCD;
	}
	return -1.0f;
}

float USkill::GetSkillCDGrowth(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].SkillCDGrowth;
	}
	return -1.0f;
}

float USkill::GetSkillCurCD(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].CurCD;
	}
	return -1.0f;
}

float USkill::SetSkillCurCD(int32 id, float NewCurCD)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].CurCD = NewCurCD;
	}
	return -1.0f;
}

float USkill::AddSkillCurCD(int32 id, float DeltaCurCD)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].CurCD += DeltaCurCD;
	}
	return -1.0f;
}

float USkill::ResetSkillCurCD(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SetSkillCurCD(id, GetSkillCD(id));
	}
	return -1.0f;
}

float USkill::GetSkillRange(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		return SkillState[id].Range;
	}
	return -1.0f;
}

int32 USkill::GetSkillPoint()
{
	return SkillPoint;
}

int32 USkill::SetSkillPoint(int32 NewPoint)
{
	return SkillPoint=NewPoint;
}

int32 USkill::AddSkillPoint(int32 DeltaPoint)
{
	return SkillPoint+= DeltaPoint;
}

bool USkill::CheckIDIsLegal(int32 id)
{
	if (id >= 0 && id < SkillState.Num()) return true;
	else return false;
}

bool USkill::SkillSingleColdDown(int32 id, float DeltaTime)
{
	if (CheckIDIsLegal(id))
	{
		if (GetSkillCurCD(id) < 0.0f)
		{
			SetSkillCurCD(id, 0.0f);
			return true;
		}
		else
		{
			AddSkillCurCD(id, -DeltaTime);
		}
		return true;
	}
	return false;
}

void USkill::SkillWholeColdDown(float DeltaTime)
{
	for (int32 i = 0; i < SkillState.Num(); ++i)
	{
		SkillSingleColdDown(i, DeltaTime);
	}
}

void USkill::SkillLevelUp(int32 id)
{

	if (CheckIDIsLegal(id))
	{
		AHero* HeroOwner = Cast<AHero>(GetOwner());
		if (HeroOwner)
		{
			if (SkillState[id].SkillRule[GetSkillLevel(id)] <= HeroOwner->PropertyComp->GetCurLevel())
			{
				if (GetSkillLevel(id) < GetMaxSkillLevel(id))
				{
					AddSkillCD(id, -1 * GetSkillCDGrowth(id));
					AddSkillMagDamage(id, GetSkillMagDamageGrowth(id));
					AddSkillMPConsume(id, GetSkillMPConsumeGrowth(id));
					AddSkillLevel(id, 1);
					AddSkillPoint(-1);
				}
			}
		}
	}
}

bool USkill::CheckCanBeReleased(int32 id)
{
	if (CheckIDIsLegal(id))
	{
		AHero* OwnerPawn = Cast<AHero>(GetOwner());
		if (OwnerPawn)
		{
			if (OwnerPawn->PropertyComp->GetCurMP() > GetSkillMPConsume(id) && GetSkillCurCD(id) < 0.0001&&GetSkillLevel(id)>0)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

void USkill::ReleaseSkill(int32 id)
{
	AHero* OwnerPawn = Cast<AHero>(GetOwner());
	MulticastSetSkillCD(id, (1 - OwnerPawn->PropertyComp->GetCurCDReduction())*GetSkillCD(id));
}

void USkill::MulticastSetSkillCD_Implementation(int32 id, float time)
{
	if (CheckIDIsLegal(id))
	{
		AHero* OwnerPawn = Cast<AHero>(GetOwner());
		OwnerPawn->PropertyComp->AddCurMP(-GetSkillMPConsume(id));
		SetSkillCurCD(id, time);
	}
}

bool USkill::MulticastSetSkillCD_Validate(int32 id, float time)
{
	return true;
}

void USkill::OwnerLevelUp()
{
	AddSkillPoint(1);
}

void USkill::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USkill, SkillState);
}

