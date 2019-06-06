// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "Perception\AIPerceptionComponent.h"
#include"Perception\AISenseConfig_Sight.h"
#include "BaseCharacter.h"

ABaseAIController::ABaseAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 3000.0f;

	SightConfig->LoseSightRadius = 3500.0f;

	SightConfig->PeripheralVisionAngleDegrees = 180.0f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;

	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComp->ConfigureSense(*SightConfig);

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this,&ABaseAIController::WhenPerceptionUpdated);

}

void ABaseAIController::WhenPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (bIsInit)
	{
		for (int32 i = 0; i < UpdatedActors.Num(); ++i)
		{
			if(UpdatedActors[i])
			{ 
				PerceptionActors.AddUnique(UpdatedActors[i]);
			}
		}
		CheckAllTarget();
		for (int32 i = 0; i < PerceptionActors.Num(); ++i)
		{
			ABaseCharacter* UnknowPawn = Cast<ABaseCharacter>(PerceptionActors[i]);
			if (UnknowPawn)
			{
				UnknowPawn->OnActorDeath.AddDynamic(this,&ABaseAIController::RemoveOneDeathActor);
			}
		}
	}
}

void ABaseAIController::CheckAllTarget()
{
	ABaseCharacter* BasePawn = Cast<ABaseCharacter>(OwnerPawn);
	if (BasePawn)
	{			
		for (int32 i = 0; i < PerceptionActors.Num(); ++i)
		{
			ABaseCharacter* UnknowPawn= Cast<ABaseCharacter>(PerceptionActors[i]);
			if (UnknowPawn)
			{
				if (BasePawn->CheckIsEnemy(UnknowPawn))
				{
					Enemys.AddUnique(PerceptionActors[i]);
					RefreshHateList(PerceptionActors[i]);
				}
				else
				{
					Friends.AddUnique(PerceptionActors[i]);
				}
			}
		}
	}
}

void ABaseAIController::RefreshHateList(AActor*Enemy)
{
	if (HateList.Num())
	{
		if (!CheckHateList(Enemy))
		{
			HateList.Add(FHateValue(Enemy, 10.0f));
		}
	}
	else
	{
		HateList.Add(FHateValue(Enemy, 10.0f));
	}
}

bool ABaseAIController::CheckHateList(AActor * Enemy)
{
	for (int32 i = 0; i < HateList.Num(); ++i)
	{
		AActor* Target=HateList[i].Enemy;
		if (Enemy == Target) return true;
		
	}
	return false;
}

float ABaseAIController::FHateValueByDistance(float Distance)
{
	if (Distance > 5000.0f) return 0;
	float K = Distance / 3000.0f;
	K = K > 1 ? 1 : K;
	return 2-1.9*K;
}
void ABaseAIController::RemoveOneDeathActor( AActor* DeathActor)
{
	if (PerceptionActors.Contains(DeathActor))
	{
		PerceptionActors.Remove(DeathActor);
		for (int32 i = 0; i < HateList.Num(); ++i)
		{
			AActor* Target = HateList[i].Enemy;
			if (DeathActor == Target)
			{
				FHateValue Removed = HateList[i];
				HateList.Remove(Removed);
			}
		}
	}
		if (Enemys.Contains(DeathActor))Enemys.Remove(DeathActor);
		else if (Friends.Contains(DeathActor))Friends.Remove(DeathActor);
}

AActor * ABaseAIController::GetAttackTarget()
{
	AActor* AttackTarget=nullptr;
	float RealHate =-1.0f;
	HateListByDistance.Empty();
	for (int32 i = 0; i < HateList.Num(); ++i)
	{
		float TempHate =FHateValueByDistance(OwnerPawn->GetDistanceTo(HateList[i].Enemy));
		if (TempHate > RealHate)
		{
			AttackTarget = HateList[i].Enemy;
			RealHate = TempHate;
		}
	}
	return AttackTarget;
}
void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}
void ABaseAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}