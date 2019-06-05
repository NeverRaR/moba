// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuff.generated.h"
class ABaseCharacter;
class UParticleSystemComponent;
UENUM(BlueprintType)
enum class BuffType :uint8 //…Ë÷√uint8¿‡–Õ
{
	BlueBuff UMETA(DisplayName = "BlueBuff"),
	RedBuff UMETA(DisplayName = "RedBuff"),
	Burning UMETA(DisplayName = "Burning"),
	KuangBuff1 UMETA(DisplayName = "KuangBuff1")
};
UCLASS()
class OURMOBA_API ABaseBuff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsBuffEnd() ;

	virtual bool BuffIsEffective(ABaseCharacter* OwnerPawn);

	virtual bool EndBuff(ABaseCharacter* OwnerPawn);

	void	EnforceEndBuff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		BuffType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsUnique = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDebuffInstigator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsChildBuff = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABaseBuff* AttachedDebuff ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SustainTime=0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurTime = 0.0f;
	
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
		APawn* Receiver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* React;

};