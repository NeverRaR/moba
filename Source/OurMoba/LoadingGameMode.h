// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoadingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OURMOBA_API ALoadingGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		void GotoNewLevel(const FString& LevelUrl, bool bAbsolute);
};
