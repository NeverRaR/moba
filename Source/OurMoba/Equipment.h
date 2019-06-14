// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment.generated.h"
class ABaseEquipment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURMOBA_API UEquipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddEquipment(ABaseEquipment*NewEquipment);  //增加装备的方法
		
	UFUNCTION(BlueprintCallable)
		void RemoveEquipment(ABaseEquipment*NewEquipment);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyGold(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurHP(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurMP(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurHPRecovery(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurMPRecovery(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurPhyAttack(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurMagAttack(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurPhyDef(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurMagDef(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurAttackSpeed(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurMoveSpeed(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurLeech(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyCurCDReduction(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseMaxHP(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseMaxMP(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseHPRecovery(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseMPRecovery(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBasePhyAttack(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseMagAttack(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBasePhyDef(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseMagDef(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseAttackSpeed(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseMoveSpeed(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseLeech(float Amount, AHero* TargetPawn);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerModifyBaseCDReduction(float Amount, AHero* TargetPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32  MaxEquipment = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseEquipment*>  AllEquipment;

};