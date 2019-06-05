// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "TwinBlast.generated.h"
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class OURMOBA_API ATwinBlast : public AHero
{
	GENERATED_BODY()
public:
		virtual void OnSetAttackPressed() override;

		virtual void  CRoleComboAttack(int32 NextIndex)override;
		void TurnToMouseLocation();

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float TurnCoefficient = 10.0f;

		virtual	void	Skill1Release() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
			UParticleSystem* Skill1React;
};
