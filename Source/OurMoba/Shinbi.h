// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "Shinbi.generated.h"
class UParticleSystem;
/**
 * 
 */
UCLASS()
class OURMOBA_API AShinbi : public AHero
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Skill1React;

	virtual	void	Skill1Release() override;
};
