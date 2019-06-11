// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Perception\AIPerceptionComponent.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "Components/ActorComponent.h"
#include "EngineDefines.h"
#include "GenericTeamAgentInterface.h"
#include "OurMobaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OURMOBA_API AOurMobaGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void GameOver();
};
