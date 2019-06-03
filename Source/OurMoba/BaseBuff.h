// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuff.generated.h"
class ABaseCharacter;
class UParticleSystemComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SustainTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMaxMP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaHPRecovery;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMPRecovery;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaPhyDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMagDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaPhyDef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMagDef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaMoveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaLeech;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeltaCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* React;

};