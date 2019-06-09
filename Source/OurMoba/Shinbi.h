// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "Shinbi.generated.h"
class UParticleSystem;
class UNavigationSystemV1;
class UNavigationSystem;
/**
 * 
 */
UCLASS()
class OURMOBA_API AShinbi : public AHero
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill1React;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill3React;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		float Skill1EffectRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		float Skill3EffectRange;

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
		virtual void MulticastSkillEffects(UParticleSystem* Particle, FVector EffectLocation);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill1Blink(FVector target);

	UFUNCTION(BlueprintCallable)
		void Skill3DeathTarget(FVector target);

	UFUNCTION(BlueprintCallable)
		void Skill2BecomeGhost();

	UFUNCTION(BlueprintCallable)
		void Skill1Blink(FVector target);

	virtual	void Skill1Release() override;

	virtual	void Skill2Release() override;

	virtual	void Skill3Release() override;
};
