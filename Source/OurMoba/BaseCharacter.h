// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureCamp.h"
#include "BaseCharacter.generated.h"
class UParticleSystem;
class UAnimiation;
class UAnimMontage;
class UCharacterProperty;
class UCreatureCamp;
class UAIManager;
UCLASS(Blueprintable)
class OURMOBA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	uint32 bIsAttacking : 1;
	uint32 bIsAlive : 1;
	uint32 bIsReadyToCombo : 1;
	int32 ComboIndex = 0;
	int32 DeathIndex = 0;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnSetAttackPressed();//将在远程单位中重写
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	uint32 IsAttacking()const { return bIsAttacking; }
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void CRoleComboAttack(int32 NextIndex);
	UFUNCTION(BlueprintCallable, Category = "Attack")
		void CRoleResetAttack() ;
	UFUNCTION(BlueprintCallable)
		void ReceivePhyDamage(float PhyDamage);
	UFUNCTION(BlueprintCallable)
		void ReceiveMagDamage(float MagDamage);
	UFUNCTION(BlueprintCallable)
		void	CPhyTraceDetect(TArray<FHitResult> HitResult);
	UFUNCTION(BlueprintCallable)
		void	CPhySingleDetect(ABaseCharacter* Target);
	UFUNCTION(BlueprintCallable)
		void	CMagTraceDetect(TArray<FHitResult> HitResult);
	UFUNCTION(BlueprintImplementableEvent)
		void DEBUGprint(float num);
	UFUNCTION(BlueprintCallable)
		void	CheckIsDead();
	UFUNCTION(BlueprintCallable)
		void	DeathOver();
	UFUNCTION(BlueprintCallable)
		TArray<ABaseCharacter*> GetAllEnemysInRadius(float Radius);
	UFUNCTION(BlueprintCallable)
		void PlayNextMontage(TArray<UAnimMontage*> Arr,int32& Index, float Rate);
	UFUNCTION(BlueprintImplementableEvent)
		void  SetFireParticle(UParticleSystem*  React);
	UFUNCTION(BlueprintImplementableEvent)
		void SetMoveSpeed(float CurSpeed);
	UFUNCTION(BlueprintImplementableEvent)
		void WholeDeath(AActor*Death);
	UFUNCTION(BlueprintCallable)
		bool CheckIsEnemy(ABaseCharacter* UnknowCharacter) { return CampComp->CheckIsEnemy(UnknowCharacter->CampComp->GetCamp()); }
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Anim", meta = (AllowPrivateAccess = "true"))
		UAnimiation* AnimiationComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
		UCharacterProperty* PropertyComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camp", meta = (AllowPrivateAccess = "true"))
		UCreatureCamp*  CampComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle", meta = (AllowPrivateAccess = "true"))
		UParticleSystem*  HitReact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle", meta = (AllowPrivateAccess = "true"))
		UParticleSystem*  DeathReact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle", meta = (AllowPrivateAccess = "true"))
		UParticleSystem*  FireReact;
};