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


		virtual	void	Skill1Release() override;

	
};
