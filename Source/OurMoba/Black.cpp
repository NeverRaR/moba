// Fill out your copyright notice in the Description page of Project Settings.


#include "Black.h"
#include"Buff.h"
#include"BlueBuff.h"
#include "Public/UObject/ConstructorHelpers.h"


ABlack::ABlack()
{

}

void ABlack::BeginPlay()
{
	Super::BeginPlay();
}

void ABlack::DeathEffect(ABaseCharacter * Attacker)
{
	if (Attacker)
	{
		BlueBuff = GetWorld()->SpawnActor<ABlueBuff>(ABlueBuff::StaticClass());
		check(BlueBuff != nullptr)
			Attacker->BuffComp->AddBuff(BlueBuff);
	}
}