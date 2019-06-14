// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include"BaseEquipment.h"
#include"Hero.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
// Sets default values for this component's properties
UEquipment::UEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipment::AddEquipment(ABaseEquipment*NewEquipment)
{
	AHero* OwnerPawn = Cast<AHero>(GetOwner());
	if (OwnerPawn)
	{
		if (AllEquipment.Num() < MaxEquipment)//不会超出最大装备数量
		{
			if (OwnerPawn->PropertyComp->GetCurMoney() >= NewEquipment->NeedGold)
			{
				NewEquipment->EquipmentIsEffective(OwnerPawn); //添加进去
				AllEquipment.Add(NewEquipment);
			}
		}
	}
}

void UEquipment::RemoveEquipment(ABaseEquipment*NewEquipment)
{
	
	AHero* OwnerPawn = Cast<AHero>(GetOwner());
	if (OwnerPawn&&NewEquipment)
	{
		NewEquipment->EndEquipment(OwnerPawn);
		AllEquipment.Remove(NewEquipment);
		NewEquipment->Destroy();
	}
}

void UEquipment::ServerModifyGold_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddMoney(Amount);
}

bool UEquipment::ServerModifyGold_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurHP_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurHP(Amount);
}

bool UEquipment::ServerModifyCurHP_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurHPRecovery_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurHPRecovery(Amount);
}

bool UEquipment::ServerModifyCurHPRecovery_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurMP_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurMP(Amount);
}

bool UEquipment::ServerModifyCurMP_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurMPRecovery_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurMPRecovery(Amount);
}

bool UEquipment::ServerModifyCurMPRecovery_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurPhyAttack_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurPhyAttack(Amount);
}

bool UEquipment::ServerModifyCurPhyAttack_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurPhyDef_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurPhyDef(Amount);
}

bool UEquipment::ServerModifyCurPhyDef_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurMagAttack_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurMagAttack(Amount);
}

bool UEquipment::ServerModifyCurMagAttack_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurMagDef_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurMagDef(Amount);
}

bool UEquipment::ServerModifyCurMagDef_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurAttackSpeed_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurAttackSpeed(Amount);
}

bool UEquipment::ServerModifyCurAttackSpeed_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurMoveSpeed_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurMoveSpeed(Amount);
}

bool UEquipment::ServerModifyCurMoveSpeed_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurLeech_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurLeech(Amount);
}

bool UEquipment::ServerModifyCurLeech_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyCurCDReduction_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddCurCDReduction(Amount);
}

bool UEquipment::ServerModifyCurCDReduction_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseMaxHP_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseMaxHP(Amount);
}

bool UEquipment::ServerModifyBaseMaxHP_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseHPRecovery_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseHPRecovery(Amount);
}

bool UEquipment::ServerModifyBaseHPRecovery_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseMaxMP_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseMaxMP(Amount);
}

bool UEquipment::ServerModifyBaseMaxMP_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseMPRecovery_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseMPRecovery(Amount);
}

bool UEquipment::ServerModifyBaseMPRecovery_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBasePhyAttack_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBasePhyAttack(Amount);
}

bool UEquipment::ServerModifyBasePhyAttack_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBasePhyDef_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBasePhyDef(Amount);
}

bool UEquipment::ServerModifyBasePhyDef_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseMagAttack_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseMagAttack(Amount);
}

bool UEquipment::ServerModifyBaseMagAttack_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseMagDef_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseMagDef(Amount);
}

bool UEquipment::ServerModifyBaseMagDef_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseAttackSpeed_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseAttackSpeed(Amount);
}

bool UEquipment::ServerModifyBaseAttackSpeed_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseMoveSpeed_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseMoveSpeed(Amount);
}

bool UEquipment::ServerModifyBaseMoveSpeed_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseLeech_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseLeech(Amount);
}

bool UEquipment::ServerModifyBaseLeech_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}

void UEquipment::ServerModifyBaseCDReduction_Implementation(float Amount, AHero * TargetPawn)
{
	TargetPawn->PropertyComp->AddBaseCDReduction(Amount);
}

bool UEquipment::ServerModifyBaseCDReduction_Validate(float Amount, AHero * TargetPawn)
{
	return true;
}