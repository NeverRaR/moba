// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "DeathFlag.generated.h"
class UParticleSystem;
/**
 * 
 */
UCLASS()
class OURMOBA_API ADeathFlag : public ABaseBuff
{
	GENERATED_BODY()

public:
	ADeathFlag();

	virtual bool EndBuff(ABaseCharacter* OwnerPawn) override;

	virtual void Tick(float DeltaTime) override;

	float ExecuteCoefficient = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* DeathExecute;
};
