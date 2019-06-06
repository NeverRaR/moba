// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Green.generated.h"
class ABaseBuff;
/**
 * 
 */
UCLASS()
class OURMOBA_API AGreen : public ABaseCharacter
{
	GENERATED_BODY()
public:
		virtual void DeathEffect(ABaseCharacter*Attacker)override;
		UPROPERTY(EditAnywhere,BlueprintReadWrite)
		ABaseBuff* RedBuff;
};
