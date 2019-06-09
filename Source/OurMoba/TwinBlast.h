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

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetAttackTarget(FVector Target);

	virtual void  CRoleComboAttack(int32 NextIndex)override;

	void TurnToMouseLocation();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetRotation(FRotator Rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TurnCoefficient = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackTarget;

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
		virtual void MulticastSkillEffects(UParticleSystem* Particle, FVector EffectLocation);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSkill1Shrapnel(FVector Target);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSkill2SelfHeal();

	UFUNCTION(BlueprintCallable)
		void Skill1Shrapnel(FVector Target);

	UFUNCTION(BlueprintCallable)
		void Skill2SelfHeal();

	virtual	void Skill1Release() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill1React;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill2React;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		float  Skill1EffectRange;

	virtual	void Skill2Release() override;
};
