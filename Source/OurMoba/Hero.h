// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Hero.generated.h"
class USkill;
class UEquipment;
/**
 * 
 */
UCLASS()
class OURMOBA_API AHero : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AHero();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UFUNCTION(BlueprintCallable)
		void Skill1Upgrade();

	UFUNCTION(BlueprintCallable)
		void Skill2Upgrade();

	UFUNCTION(BlueprintCallable)
		void Skill3Upgrade();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill1Upgrade();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill2Upgrade();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSkill3Upgrade();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation)
		void MulticastSkill1Upgrade();

	UFUNCTION(BlueprintCallable, NetMulticast, Server, Reliable, WithValidation)
		void MulticastSkill2Upgrade();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation)
		void MulticastSkill3Upgrade();

	UFUNCTION(BlueprintCallable)
		virtual	void Skill1Release();

	UFUNCTION(BlueprintCallable)
		virtual	void Skill2Release();

	UFUNCTION(BlueprintCallable)
		virtual	void Skill3Release();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		virtual	void ServerSkill1Release();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		virtual	void ServerSkill2Release();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		virtual	void ServerSkill3Release();

	UFUNCTION(BlueprintCallable)
		void PhyDamageEnemy(TArray<ABaseCharacter*> Arr);

	UFUNCTION(BlueprintCallable)
		FVector GetMouseLocation();

	UFUNCTION(BlueprintImplementableEvent)
		void UISkill1Upgrade();

	UFUNCTION(BlueprintImplementableEvent)
		void UISkill2Upgrade();

	UFUNCTION(BlueprintImplementableEvent)
		void UISkill3Upgrade();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		USkill* SkillComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
		UEquipment* EquipmentComp;
};
