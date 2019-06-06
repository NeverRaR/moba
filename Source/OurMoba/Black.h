// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Black.generated.h"
class ABaseBuff;
class ABlueBuff;
/**
 * 
 */
UCLASS()
class OURMOBA_API ABlack : public ABaseCharacter
{
	GENERATED_BODY()
public:
	virtual void DeathEffect(ABaseCharacter*Attacker)override;

	ABlack();

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABlueBuff* BlueBuff;
};
