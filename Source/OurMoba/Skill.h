// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception\AIPerceptionComponent.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "Components/ActorComponent.h"
#include "EngineDefines.h"
#include "GenericTeamAgentInterface.h"
#include "Skill.generated.h"
USTRUCT(BlueprintType)
struct FSkillBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		float SkillCD=12.0f;
	UPROPERTY(EditAnywhere)
		float CurCD=0.0f;
	UPROPERTY(EditAnywhere)
		float MPConsume = 50.0f;
	UPROPERTY(EditAnywhere)
		float MPConsumeGrowth = 10.0f;
	UPROPERTY(EditAnywhere)
		float MagDamage=100.0f;
	UPROPERTY(EditAnywhere)
		int32 SkillLevel=0;
	UPROPERTY(EditAnywhere)
		int32 MaxSkillLevel = 6;
	UPROPERTY(EditAnywhere)
		float SkillCDGrowth=0.6f;
	UPROPERTY(EditAnywhere)
		float MagDamageGrowth=50.0f;
	UPROPERTY(EditAnywhere)
		float Range=1500.0f;
	UPROPERTY(EditAnywhere)
		TArray<int32> SkillRule = { 1,3,5,7,9,11 };
	
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURMOBA_API USkill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkill();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//SkillLeveL
	UFUNCTION(BlueprintCallable)
		int32 GetSkillLevel(int32 id);

	UFUNCTION(BlueprintCallable)
		int32 GetMaxSkillLevel(int32 id);

	UFUNCTION(BlueprintCallable)
		int32 SetSkillLevel(int32 id,int32 NewLevel);

	UFUNCTION(BlueprintCallable)
		int32 AddSkillLevel(int32 id,int32 DeltaLevel);
	

	//Damage
	UFUNCTION(BlueprintCallable)
		float GetSkillMagDamage(int32 id);
	
	UFUNCTION(BlueprintCallable)
		float SetSkillMagDamage(int32 id, float NewMagDamage);
	
	UFUNCTION(BlueprintCallable)
		float AddSkillMagDamage(int32 id, float DeltaMagDamage);
	
	UFUNCTION(BlueprintCallable)
		float GetSkillMagDamageGrowth(int32 id);
	
	UFUNCTION(BlueprintCallable)
		float GetSkillMPConsume(int32 id);

	UFUNCTION(BlueprintCallable)
		float SetSkillMPConsume(int32 id, float NewMPConsume);

	UFUNCTION(BlueprintCallable)
		float AddSkillMPConsume(int32 id, float DeltaMPConsume);

	UFUNCTION(BlueprintCallable)
		float GetSkillMPConsumeGrowth(int32 id);

	//CD
	UFUNCTION(BlueprintCallable)
		float GetSkillCD(int32 id);
	
	UFUNCTION(BlueprintCallable)
		float SetSkillCD(int32 id, float NewCD);
	
	UFUNCTION(BlueprintCallable)
		float AddSkillCD(int32 id, float DeltaCD);
	
	UFUNCTION(BlueprintCallable)
		float GetSkillCDGrowth(int32 id);
	
	UFUNCTION(BlueprintCallable)
		float GetSkillCurCD(int32 id);
	
	UFUNCTION(BlueprintCallable)
		float SetSkillCurCD(int32 id, float NewCurCD);
	
	UFUNCTION(BlueprintCallable)
		float AddSkillCurCD(int32 id, float DeltaCurCD);
	
	UFUNCTION(BlueprintCallable)
		float ResetSkillCurCD(int32 id);

	UFUNCTION(BlueprintCallable)
		float GetSkillRange(int32 id);

	UFUNCTION(BlueprintCallable)
		int32 GetSkillPoint();

	UFUNCTION(BlueprintCallable)
		int32 SetSkillPoint(int32 NewPoint);

	UFUNCTION(BlueprintCallable)
		int32 AddSkillPoint(int32 DeltaPoint);

	UFUNCTION(BlueprintCallable)
		bool CheckIDIsLegal(int32 id);

	UFUNCTION(BlueprintCallable)
		bool SkillSingleColdDown(int32 id, float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void SkillWholeColdDown(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void SkillLevelUp(int32 id);

	UFUNCTION(BlueprintCallable)
		bool CheckCanBeReleased(int32 id);

	UFUNCTION(BlueprintCallable)
	    void  ReleaseSkill(int32 id);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation)
		void MulticastSetSkillCD(int32 id, float time);

		void OwnerLevelUp();

		void DeathSilent();
private:

	UPROPERTY(EditAnywhere, Replicated)
		TArray<FSkillBase> SkillState;

	UPROPERTY(EditAnywhere)
	     int32 SkillPoint;
};