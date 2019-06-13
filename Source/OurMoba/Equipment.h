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

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerAddEquipmentToClient(ABaseEquipment*NewEquipment, AHero* TargetPawn);

	UFUNCTION(BlueprintCallable)
		void AddEquipmentToServer(ABaseEquipment*NewEquipment, AHero* TargetPawn);
		
	UFUNCTION(BlueprintCallable)
		void RemoveEquipment(ABaseEquipment*NewEquipment);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRemoveEquipmentFromClient(ABaseEquipment*NewEquipment, AHero* TargetPawn);

	UFUNCTION(BlueprintCallable)
		void RemoveEquipmentFromServer(ABaseEquipment*NewEquipment, AHero* TargetPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32  MaxEquipment = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseEquipment*>  AllEquipment;

};