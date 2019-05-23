// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CreatureCamp.generated.h"

UENUM(BlueprintType)
enum class CharacterCamp :uint8 //设置uint8类型
{
	Dawn UMETA(DisplayName = "Dawn"),
	Dust UMETA(DisplayName = "Dust"),
	Neutral UMETA(DisplayName = "Neutral")
};
UENUM(BlueprintType)
enum class CharacterGroup :uint8 //设置uint8类型
{
	Minion UMETA(DisplayName = "Minion"),
	Hero UMETA(DisplayName = "Hero"),
	Turret UMETA(DisplayName = "Turret")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURMOBA_API UCreatureCamp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCreatureCamp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	CharacterCamp GetCamp() { return Camp; }
	CharacterGroup GetGroup() { return Group; }
	CharacterCamp SetCamp(const CharacterCamp& NewCamp) { return Camp= NewCamp; }
	CharacterGroup SetGroup(const CharacterGroup& NewGroup) { return Group= NewGroup; }


private:
	UPROPERTY(EditAnywhere)
		CharacterCamp Camp;
	UPROPERTY(EditAnywhere)
		CharacterGroup Group;
};
