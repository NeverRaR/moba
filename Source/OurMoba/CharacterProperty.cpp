// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterProperty.h"
#include"OurMobaGameMode.h"
#include "Hero.h"
#include"Skill.h"
#include"Net/UnrealNetwork.h"
// Sets default values for this component's properties
UCharacterProperty::UCharacterProperty()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UCharacterProperty::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UCharacterProperty::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HPRecovering(DeltaTime);
	MPRecovering(DeltaTime);
	AddMoney(DeltaTime);
	// ...
}

bool UCharacterProperty::LevelUp()
{
	if (bIsLevelUp)
	{
		AddLevel(1);
		AddBaseMaxHP(FBasePropertyDetail.HPGrowth);
		AddBaseMaxMP(FBasePropertyDetail.MPGrowth);
		AddBaseHPRecovery(FBasePropertyDetail.HPRecoveryGrowth);
		AddBaseMPRecovery(FBasePropertyDetail.MPRecoveryGrowth);
		AddBasePhyAttack(FBasePropertyDetail.PhyAttackGrowth);
		AddBaseMagAttack(FBasePropertyDetail.MagAttackGrowth);
		AddBasePhyDef(FBasePropertyDetail.PhyDefGrowth);
		AddBaseMagDef(FBasePropertyDetail.MagDefGrowth);
		AddBaseAttackSpeed(FBasePropertyDetail.AttackSpeedGrowth);
		AddCurMaxHP(FBasePropertyDetail.HPGrowth);
		AddCurMaxMP(FBasePropertyDetail.MPGrowth);
		AddCurHP(FBasePropertyDetail.HPGrowth);
		AddCurMP(FBasePropertyDetail.MPGrowth);
		AddCurHPRecovery(FBasePropertyDetail.HPRecoveryGrowth);
		AddCurMPRecovery(FBasePropertyDetail.MPRecoveryGrowth);
		AddCurPhyAttack(FBasePropertyDetail.PhyAttackGrowth);
		AddCurMagAttack(FBasePropertyDetail.MagAttackGrowth);
		AddCurPhyDef(FBasePropertyDetail.PhyDefGrowth);
		AddCurMagDef(FBasePropertyDetail.MagDefGrowth);
		AddCurAttackSpeed(FBasePropertyDetail.AttackSpeedGrowth);
		AddMoneyWorth(FBasePropertyDetail.MoneyWorthGrowth);
		AddEXPWorth(FBasePropertyDetail.EXPWorthGrowth);
		bIsLevelUp = false;
		AHero* OwnerHero = Cast<AHero>(GetOwner());
		if (OwnerHero)
		{
			OwnerHero->SkillComp->OwnerLevelUp();
		}
		return true;
	}
	else
	{
		return false;
	}
}

void UCharacterProperty::ResetCurProperty()
{
	SetCurHP(GetBaseMaxHP());
	SetCurMaxHP(GetBaseMaxHP());
	SetCurMP(GetBaseMaxMP());
	SetCurMaxMP(GetBaseMaxMP());
	SetCurHPRecovery(GetBaseHPRecovery());
	SetCurMPRecovery(GetBaseMPRecovery());
	SetCurPhyAttack(GetBasePhyAttack());
	SetCurMagAttack(GetBaseMagAttack());
	SetCurPhyDef(GetBasePhyDef());
	SetCurMagDef(GetBaseMagDef());
	SetCurAttackSpeed(GetBaseAttackSpeed());
	SetCurMoveSpeed(GetBaseMoveSpeed());
}

void UCharacterProperty::HPRecovering(float DeltaTime)
{
	if (IsAlive())
	{
		float FlameRecovery = GetCurHPRecovery() * DeltaTime;
		if (GetCurHP() < GetCurMaxHP())
		{
			AddCurHP(FlameRecovery);
			if (GetCurHP() > GetCurMaxHP()) SetCurHP(GetCurMaxHP());
		}
		else SetCurHP(GetCurMaxHP());
	}

}

void UCharacterProperty::MPRecovering(float DeltaTime)
{
	if (IsAlive())
	{
		float FlameRecovery = GetCurMPRecovery() * DeltaTime;
		if (GetCurMP() < GetCurMaxMP())
		{
			AddCurMP(FlameRecovery);
			if (GetCurMP() > GetCurMaxMP()) SetCurMP(GetCurMaxMP());
		}
		else  SetCurMP(GetCurMaxMP());
	}

}

bool UCharacterProperty::CheckLevelUp(float DeltaEXP)
{
	if (GetCurLevel() >= MaxLevel)
	{
		SetLevel(MaxLevel);
		SetEXP(FBasePropertyDetail.LevelRule[MaxLevel - 1] + 1.0);//防止经验和等级溢出
		bIsLevelUp = false;
	}
	if (AddEXP(DeltaEXP) > FBasePropertyDetail.LevelRule[GetCurLevel()])
	{
		bIsLevelUp = true;
	}
	else
	{
		bIsLevelUp = false;
	}
	return LevelUp();
}

void UCharacterProperty::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UCharacterProperty, FCurPropertyDetail);
	
	DOREPLIFETIME(UCharacterProperty, FBasePropertyDetail);
}

