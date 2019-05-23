// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction.h"
#include "BaseCharacter.h"
#include "Engine\EngineTypes.h"
// Sets default values for this component's properties
UInteraction::UInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteraction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteraction::CTraceDetect(TArray<FHitResult> HitResult)
{
	TArray<AActor*> Ignored;
	ABaseCharacter* BaseOwner = Cast<ABaseCharacter>(GetOwner());
	if (BaseOwner)
	{   
		float Damage = BaseOwner->PropertyComp->GetCurPhyAttack();
		for (int32 i = 0; i < HitResult.Num(); ++i)
		{
			if (Ignored.Contains(HitResult[i].Actor)) continue;
			ABaseCharacter* Receiver = Cast<ABaseCharacter>(HitResult[i].Actor);
			if (Receiver)
			{
				Receiver->ReceivePhyDamage(Damage);
				DEBUGprint(Receiver->PropertyComp->GetCurHP());
			}
		}
	}
}




