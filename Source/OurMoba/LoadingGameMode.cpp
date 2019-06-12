// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingGameMode.h"
#include "Engine/World.h"

void ALoadingGameMode::GotoNewLevel(const FString& LevelUrl, bool bAbsolute)
{
	if (Role < ROLE_Authority) return;

	GetWorld()->ServerTravel(LevelUrl, bAbsolute, true);
}
