// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEquipment.generated.h"
class AHero;
class UParticleSystemComponent;
UENUM(BlueprintType)
enum class EquipmentType :uint8 //设置uint8类型
{
	EquipmentOne UMETA(DisplayName = "EquipmentOne"),
/*
    EquipmentTwo UMETA(DisplayName = "EquipmentTwo"),
    EquipmentThree UMETA(DisplayName = "EquipmentThree"),
	EquipmentFour UMETA(DisplayName = "EquipmentFour"),
	EquipmentFive UMETA(DisplayName = "EquipmentFive"),
	EquipmentSix UMETA(DisplayName = "EquipmentSix"),
	EquipmentSeven UMETA(DisplayName = "EquipmentSeven"),
	EquipmentEight UMETA(DisplayName = "EquipmentEight")
*/
};

UCLASS()  
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool EquipmentIsEffective(AHero* OwnerPawn);//装备生效的方法

	virtual bool EndEquipment(AHero* OwnerPawn);//装备结束生效的方法

	virtual bool GoldEnough(float CurGold);//判断金钱是否足够

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EquipmentType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NeedGold = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMaxHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMaxMP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaHPRecovery = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMPRecovery = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaPhyDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMagDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaPhyDef = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMagDef = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMoveSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaAttackSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaLeech = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaCDReduction = 0.0f;

	UPROPERTY(EditAnywhere)
		AHero* Receiver;

};
