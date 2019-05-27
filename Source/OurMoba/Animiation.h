// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animiation.generated.h"
class UAnimMontage;
UENUM(BlueprintType)
enum class AnimationType :uint8 //…Ë÷√uint8¿‡–Õ
{
	Attack UMETA(DisplayName = "Attack"),
	Death UMETA(DisplayName = "Death"),
	Recall UMETA(DisplayName = "Recall")
};
UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURMOBA_API UAnimiation : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimiation();
 
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		UAnimMontage* GetAnimByTypeAndIndex(AnimationType Type, int32 Index);
	UFUNCTION(BlueprintCallable)
		TArray<UAnimMontage*> GetAllAnimByType(AnimationType Type);
	UFUNCTION(BlueprintCallable)
		UAnimMontage* GetRandomAnimByType(AnimationType Type);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>AttackAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death", meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>DeathAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recal", meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>RecalAnim;
	
};
