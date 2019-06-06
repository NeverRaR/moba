// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Buff.generated.h"
class ABaseBuff;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURMOBA_API UBuff : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuff();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddBuff(ABaseBuff*NewBuff);

	UFUNCTION(BlueprintCallable)
		void RemoveBuff(ABaseBuff*NewBuff, TArray<ABaseBuff*>&Arr);

	UFUNCTION(BlueprintCallable)
		void CheckAllBuff(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void ClearAllBuff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseBuff*>  MultiBuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseBuff*>  UniqueBuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseBuff*> ReleaseDebuff;
};
