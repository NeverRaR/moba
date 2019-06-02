// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAIManager;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FHateValue
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Enemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;
	FHateValue() = default;
	FHateValue(AActor* Enemy, float Value) :Enemy(Enemy), Value(Value) {};
	bool operator ==(const FHateValue& HV) { return Enemy == HV.Enemy; };
};
UCLASS()
class OURMOBA_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
		ABaseAIController();
		UFUNCTION(BlueprintCallable)
			void WhenPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

		UFUNCTION(BlueprintCallable)
			void CheckAllTarget() ;

		UFUNCTION(BlueprintCallable)
			void RefreshHateList(AActor*Enemy);

		UFUNCTION(BlueprintCallable)
			bool CheckHateList(AActor*Enemy);

		UFUNCTION(BlueprintCallable)
			float FHateValueByDistance(float Distance);

		UFUNCTION(BlueprintCallable)
			void RemoveOneDeathActor(AActor* DeathActor);

		UFUNCTION(BlueprintCallable)
			AActor* GetAttackTarget();

		UFUNCTION(BlueprintImplementableEvent)
			void DEBUGprint(float num);



protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APawn* OwnerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAIManager* AIComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> PerceptionActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> Enemys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*>  Friends;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FHateValue>  HateList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FHateValue>  HateListByDistance;
};