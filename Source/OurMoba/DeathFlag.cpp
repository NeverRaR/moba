// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathFlag.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystemComponent.h"
#include"Particles\ParticleSystem.h"
#include"UObject/ConstructorHelpers.h"
#include"Kismet\GameplayStatics.h"
#include"Components\CapsuleComponent.h"
ADeathFlag::ADeathFlag()
{
	SustainTime = 4.0f;
	bIsUnique = false;
	Type = BuffType::GhostForm;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemMaterialAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_Execute_v3.P_Execute_v3'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		React->Template = ParticleSystemMaterialAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DeathExecuteAsset(TEXT("ParticleSystem'/Game/Game/Particle/P_LevelUp.P_LevelUp'"));
	if (ParticleSystemMaterialAsset.Succeeded())
	{
		DeathExecute = DeathExecuteAsset.Object;
	}
}

bool ADeathFlag::EndBuff(ABaseCharacter * OwnerPawn)
{
	if (OwnerPawn&&OwnerPawn->PropertyComp->IsAlive())
	{
		UCharacterProperty* MyProperty = OwnerPawn->PropertyComp;
		MyProperty->AddCurPhyDef(-DeltaPhyDef);
		MyProperty->AddCurMoveSpeed(-DeltaMoveSpeed);
		float ExcuteDamage = ( (MyProperty->GetCurMaxHP() - MyProperty->GetCurHP())+MyProperty->GetCurPhyDef()*0.1f)*ExecuteCoefficient ;
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathExecute, OwnerPawn->GetActorLocation());
		OwnerPawn->ReceivePhyDamage(ExcuteDamage, Attacker);
		return true;
	}
	return false;
}


void ADeathFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Receiver)
	{
		float Radius, Hight;
		Receiver->GetCapsuleComponent()->GetScaledCapsuleSize(Radius, Hight);
		FVector Location = Receiver->GetActorLocation();
		Location.Z += Hight;
		
		if (React)
		{

			React->SetWorldLocation(Location);
			Receiver->ReceiveMagDamage(5.0f*DeltaTime, Attacker);
		}
	}
}