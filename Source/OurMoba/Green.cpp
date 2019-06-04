// Fill out your copyright notice in the Description page of Project Settings.


#include "Green.h"
#include"Buff.h"
#include"RedBuff.h"



void AGreen::DeathEffect(ABaseCharacter * Attacker)
{
	RedBuff = GetWorld()->SpawnActor<ARedBuff>(ARedBuff::StaticClass());
	Attacker->BuffComp->AddBuff(RedBuff);
}
