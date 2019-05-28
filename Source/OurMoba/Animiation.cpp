// Fill out your copyright notice in the Description page of Project Settings.


#include "Animiation.h"
#include "random"
#include"time.h"
#include"Classes\Animation\AnimMontage.h"

// Sets default values for this component's properties
UAnimiation::UAnimiation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimiation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAnimiation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
UAnimMontage * UAnimiation::GetAnimByTypeAndIndex(AnimationType Type, int32 Index)
{
	switch (Type)
	{
		case AnimationType::Attack:
			return AttackAnim[Index];
		case AnimationType::Death:
			return DeathAnim[Index];
		case AnimationType::Recall:
			return RecalAnim[Index];
		default:
			return nullptr;
	}
}

TArray<UAnimMontage*> UAnimiation::GetAllAnimByType(AnimationType Type)
{
	switch (Type)
	{
	case AnimationType::Attack:
		return AttackAnim;
	case AnimationType::Death:
		return DeathAnim;
	case AnimationType::Recall:
		return RecalAnim;
	default:
		return TArray<UAnimMontage*>();
	}
}

UAnimMontage * UAnimiation::GetRandomAnimByType(AnimationType Type)
{
	srand(time(0));
	int32 RNumber = rand();
	switch (Type)
	{
	case AnimationType::Attack:
		 RNumber%=AttackAnim.Num();
		 break;
	case AnimationType::Death:
		RNumber %= DeathAnim.Num();
		break;
	case AnimationType::Recall:
		RNumber %= DeathAnim.Num();
		break;
	default:
		return nullptr;
	}
	return GetAnimByTypeAndIndex(Type, RNumber);
}

