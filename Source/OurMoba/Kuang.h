// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "Kuang.generated.h"
class UParticleSystem;
/**
 * 
 */
UCLASS()
class OURMOBA_API AKuang : public AHero
{
	GENERATED_BODY()
public:
	AKuang();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill1React;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		float Skill1EffectRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill2React;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		float Skill2EffectRange;

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
	virtual void MulticastSkillEffects(UParticleSystem* Particle, FVector EffectLocation);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill1Thunder(FVector Target);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill2LightDurance(FVector Target);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill3Frenzy();

	UFUNCTION(BlueprintCallable)
		void Skill1Thunder(FVector Target);

	UFUNCTION(BlueprintCallable)
		void Skill2LightDurance(FVector Target);

	UFUNCTION(BlueprintCallable)
		void Skill3Frenzy();

	virtual	void Skill1Release() override;

	virtual	void Skill2Release() override;

	virtual	void Skill3Release() override;
};
