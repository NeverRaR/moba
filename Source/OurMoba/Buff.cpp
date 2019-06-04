// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff.h"
#include"BaseBuff.h"
#include"BaseCharacter.h"
#include"CharacterProperty.h"
#include"Particles\ParticleSystem.h"
#include"Particles\ParticleSystemComponent.h"
// Sets default values for this component's properties
UBuff::UBuff()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UBuff::BeginPlay()
{
	Super::BeginPlay();


	// ...
	
}


// Called every frame
void UBuff::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckAllBuff(DeltaTime);
	// ...
}

void UBuff::AddBuff(ABaseBuff * NewBuff)
{
	ABaseCharacter* OwnerPawn = Cast<ABaseCharacter>(GetOwner());
	if (NewBuff->bIsDebuffInstigator)
	{
		if (NewBuff->AttachedDebuff)
		{
			ReleaseDebuff.Add(NewBuff->AttachedDebuff);
		}
	}
	if (OwnerPawn)
	{
		if (NewBuff->bIsUnique)
		{
			for (int32 i = 0; i < UniqueBuff.Num(); ++i)
			{
				if (UniqueBuff[i]->Type == NewBuff->Type)
				{
					UniqueBuff[i]->CurTime = 0.0f;
					return;
				}
			}
			NewBuff->BuffIsEffective(OwnerPawn);
			UniqueBuff.Add(NewBuff);
		}
		else
		{
			NewBuff->BuffIsEffective(OwnerPawn);
			MultiBuff.Add(NewBuff);
		}
	}
}

void UBuff::RemoveBuff(ABaseBuff * NewBuff, TArray<ABaseBuff*>&Arr)
{
	if (Arr.Contains(NewBuff))
	{
		ABaseCharacter* OwnerPawn = Cast<ABaseCharacter>(GetOwner());
		if (OwnerPawn)
		{
			NewBuff->EndBuff(OwnerPawn);
			UniqueBuff.Remove(NewBuff);
			if (NewBuff->bIsDebuffInstigator)
			{
				if (NewBuff->AttachedDebuff)
				{
					if (ReleaseDebuff.Contains(NewBuff->AttachedDebuff))
					{
						ReleaseDebuff.Remove(NewBuff->AttachedDebuff);
						NewBuff->AttachedDebuff->Destroy();
					}
				}
			}
			NewBuff->Destroy();
		}
	}
}

void UBuff::CheckAllBuff(float DeltaTime)
{
	for (int32 i = 0; i < UniqueBuff.Num(); ++i)
	{
		if (UniqueBuff[i]->IsBuffEnd())
		{
			ABaseBuff* RemovedBuff = UniqueBuff[i];
			RemoveBuff( RemovedBuff,UniqueBuff);
		}
		else
		{
			UniqueBuff[i]->CurTime += DeltaTime;
		}
	}
	for (int32 i = 0; i < MultiBuff.Num(); ++i)
	{
		if (MultiBuff[i]->IsBuffEnd())
		{
			ABaseBuff* RemovedBuff = MultiBuff[i];
			RemoveBuff(RemovedBuff, MultiBuff);
		}
		else
		{
			MultiBuff[i]->CurTime += DeltaTime;
		}
	}
}

void UBuff::ClearAllBuff()
{
	for (int32 i = 0; i < UniqueBuff.Num(); ++i)
	{
		ABaseBuff* RemovedBuff = UniqueBuff[i];
		RemoveBuff(RemovedBuff, UniqueBuff);
	}
	for (int32 i = 0; i < MultiBuff.Num(); ++i)
	{
		ABaseBuff* RemovedBuff = MultiBuff[i];
		RemoveBuff(RemovedBuff, MultiBuff);
	}
}

