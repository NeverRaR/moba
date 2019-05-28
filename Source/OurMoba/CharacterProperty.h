// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterProperty.generated.h"
USTRUCT(BlueprintType)
struct FBaseProperty
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float HP = 685.9f;
	UPROPERTY(EditAnywhere)
		float HPGrowth = 78.0f;
	UPROPERTY(EditAnywhere)
		float MP = 303.6f;
		float MPGrowth = 17.25f;
	UPROPERTY(EditAnywhere)	
		float HPRecovery = 1.14f;
	UPROPERTY(EditAnywhere)
		float HPRecoveryGrowth = 0.13f;
	UPROPERTY(EditAnywhere)
		float MPRecovery = 1.41f;
	UPROPERTY(EditAnywhere)
		float MPRecoveryGrowth = 0.06f;
	UPROPERTY(EditAnywhere)
		float PhyAttack = 60.4f;//物理攻击
	UPROPERTY(EditAnywhere)
		float PhyAttackGrowth = 3.85f;
	UPROPERTY(EditAnywhere)
		float MagAttack = 0.0f;//魔法攻击
	UPROPERTY(EditAnywhere)
		float MagAttackGrowth = 0.0f;
	UPROPERTY(EditAnywhere)
		float PhyDef = 25.2f;//物理防御
	UPROPERTY(EditAnywhere)
		float PhyDefGrowth = 2.92f;
	UPROPERTY(EditAnywhere)
		float MagDef = 25.0f;//魔法防御
	UPROPERTY(EditAnywhere)
		float MagDefGrowth = 0.0f;
	UPROPERTY(EditAnywhere)
		float AttackSpeed = 1.18f;
	UPROPERTY(EditAnywhere)
		float AttackSpeedGrowth = 0.025f;
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
		float InitEXP = 0.0f;
	//LevelRule[k]表示第k级经验上限
	    TArray<float> LevelRule{ 0.0f,100.0f,300.0f,500.0f,800.0f,1300.0f,2150.0f,2900.0f,3900.0f,5400.0f,
			                                  // 0    1         2         3		    4          5           6           7           8           9          
			                                     6900.0f,8900.0f,11000.0f,13500.0f,16000.0f,19000.0f,999999999.0f };
	                                         //10         11         12          13            14          15           16
	UPROPERTY(EditAnywhere)
		int32 InitLevel = 1;
	UPROPERTY(EditAnywhere)
		float AttackRange=400.0f;
	UPROPERTY(EditAnywhere)
		float AttackedRange = 400.0f;

};
USTRUCT(BlueprintType)
struct FCurProperty
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float CurHP = 685.9f;
	UPROPERTY(EditAnywhere)
		float MaxHP = 685.9f;
	UPROPERTY(EditAnywhere)
		float	CurMP = 303.6f;
	UPROPERTY(EditAnywhere)
		float	MaxMP = 303.6f;
	UPROPERTY(EditAnywhere)
		float	HPRecovery = 1.14f;
	UPROPERTY(EditAnywhere)
		float	MPRecovery = 1.41f;
	UPROPERTY(EditAnywhere)
		float	PhyAttack = 60.4f;//物理攻击
	UPROPERTY(EditAnywhere)
		float	MagAttack = 0.0f;//魔法攻击
	UPROPERTY(EditAnywhere)
		float	PhyDef = 25.2f;//物理防御
	UPROPERTY(EditAnywhere)
		float	MagDef = 25.0f;//魔法防御
	UPROPERTY(EditAnywhere)
		float	AttackSpeed = 1.18f;
	UPROPERTY(EditAnywhere)
		float	MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
		float	CurEXP = 0.0f;
	UPROPERTY(EditAnywhere)
		int32 CurLevel = 1;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURMOBA_API UCharacterProperty : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterProperty();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//HP and MP
	UFUNCTION(BlueprintCallable)
		float GetBaseMaxHP() { return FBasePropertyDetail.HP; }
	UFUNCTION(BlueprintCallable)
		float GetCurHP() { return FCurPropertyDetail.CurHP; }
	UFUNCTION(BlueprintCallable)
		float GetCurMaxHP() { return FCurPropertyDetail.MaxHP; }
	UFUNCTION(BlueprintCallable)
		float GetBaseHPRecovery() { return FBasePropertyDetail.HPRecovery; }
	UFUNCTION(BlueprintCallable)
		float GetCurHPRecovery() { return FCurPropertyDetail.HPRecovery; }
	UFUNCTION(BlueprintCallable)
		float SetBaseMaxHP(float NewHP) { return FBasePropertyDetail.HP = NewHP; }
	UFUNCTION(BlueprintCallable)
		float SetCurHP(float NewHP) { return FCurPropertyDetail.CurHP = NewHP; }
	UFUNCTION(BlueprintCallable)
		float SetCurMaxHP(float NewHP) { return  FCurPropertyDetail.MaxHP = NewHP; }
	UFUNCTION(BlueprintCallable)
		float SetBaseHPRecovery(float NewHPRecovery) { return FBasePropertyDetail.HPRecovery = NewHPRecovery; }
	UFUNCTION(BlueprintCallable)
		float SetCurHPRecovery(float NewHPRecovery) { return FCurPropertyDetail.HPRecovery = NewHPRecovery; }
	UFUNCTION(BlueprintCallable)
		float AddBaseMaxHP(float DeltaHP) { return FBasePropertyDetail.HP += DeltaHP; }
	UFUNCTION(BlueprintCallable)
		float AddCurHP(float DeltaHP) { return FCurPropertyDetail.CurHP += DeltaHP; }
	UFUNCTION(BlueprintCallable)
		float AddCurMaxHP(float DeltaHP) { return  FCurPropertyDetail.MaxHP += DeltaHP; }
	UFUNCTION(BlueprintCallable)
		float AddBaseHPRecovery(float DeltaHPRecovery) { return FBasePropertyDetail.HPRecovery += DeltaHPRecovery; }
	UFUNCTION(BlueprintCallable)
		float AddCurHPRecovery(float DeltaHPRecovery) { return FCurPropertyDetail.HPRecovery += DeltaHPRecovery; }
	UFUNCTION(BlueprintCallable)
		float GetBaseMaxMP() { return FBasePropertyDetail.MP; }
	UFUNCTION(BlueprintCallable)
		float GetCurMP() { return FCurPropertyDetail.CurMP; }
	UFUNCTION(BlueprintCallable)
		float GetCurMaxMP() { return FCurPropertyDetail.MaxMP; }
	UFUNCTION(BlueprintCallable)
		float GetBaseMPRecovery() { return FBasePropertyDetail.MPRecovery; }
	UFUNCTION(BlueprintCallable)
		float GetCurMPRecovery() { return FCurPropertyDetail.MPRecovery; }
	UFUNCTION(BlueprintCallable)
		float SetBaseMaxMP(float NewMP) { return FBasePropertyDetail.MP = NewMP; }
	UFUNCTION(BlueprintCallable)
		float SetCurMP(float NewMP) { return FCurPropertyDetail.CurMP = NewMP; }
	UFUNCTION(BlueprintCallable)
		float SetCurMaxMP(float NewMP) { return  FCurPropertyDetail.MaxMP = NewMP; }
	UFUNCTION(BlueprintCallable)
		float SetBaseMPRecovery(float NewMPRecovery) { return FBasePropertyDetail.MPRecovery = NewMPRecovery; }
	UFUNCTION(BlueprintCallable)
		float SetCurMPRecovery(float NewMPRecovery) { return FCurPropertyDetail.MPRecovery = NewMPRecovery; }
	UFUNCTION(BlueprintCallable)
		float AddBaseMaxMP(float DeltaMP) { return FBasePropertyDetail.MP += DeltaMP; }
	UFUNCTION(BlueprintCallable)
		float AddCurMP(float DeltaMP) { return FCurPropertyDetail.CurMP += DeltaMP; }
	UFUNCTION(BlueprintCallable)
		float AddCurMaxMP(float DeltaMP) { return  FCurPropertyDetail.MaxMP += DeltaMP; }
	UFUNCTION(BlueprintCallable)
		float AddBaseMPRecovery(float DeltaMPRecovery) { return FBasePropertyDetail.MPRecovery; }
	UFUNCTION(BlueprintCallable)
		float AddCurMPRecovery(float DeltaMPRecovery) { return FCurPropertyDetail.MPRecovery; }


	//Level and EXP
	UFUNCTION(BlueprintCallable)
		float GetCurEXP() { return FCurPropertyDetail.CurEXP; }
	UFUNCTION(BlueprintCallable)
		float SetEXP(float NewEXP) { return FCurPropertyDetail.CurEXP = NewEXP; }
	UFUNCTION(BlueprintCallable)
		float AddEXP(float DeltaEXP) { return FCurPropertyDetail.CurEXP += DeltaEXP; }
	UFUNCTION(BlueprintCallable)
		float GetCurLevel() { return FCurPropertyDetail.CurLevel; }
	UFUNCTION(BlueprintCallable)
		float SetLevel(float NewLevel) { return FCurPropertyDetail.CurLevel = NewLevel; }
	UFUNCTION(BlueprintCallable)
		float AddLevel(float DeltaLevel) { return FCurPropertyDetail.CurLevel += DeltaLevel; }
	UFUNCTION(BlueprintCallable)
		bool CheckLevelUp(float DeltaEXP);
	UFUNCTION(BlueprintCallable)
		bool IsLevelUp() { return bIsLevelUp; }
	UFUNCTION(BlueprintCallable)
		bool LevelUp();
	//Attack and Def
	UFUNCTION(BlueprintCallable)
		float GetBasePhyAttack() { return FBasePropertyDetail.PhyAttack; }
	UFUNCTION(BlueprintCallable)
		float GetCurPhyAttack() { return FCurPropertyDetail.PhyAttack; }
	UFUNCTION(BlueprintCallable)
		float GetBaseMagAttack() { return FBasePropertyDetail.MagAttack; }
	UFUNCTION(BlueprintCallable)
		float GetCurMagAttack() { return FCurPropertyDetail.MagAttack; }
	UFUNCTION(BlueprintCallable)
		float SetBasePhyAttack(float NewAttack) { return FBasePropertyDetail.PhyAttack = NewAttack; }
	UFUNCTION(BlueprintCallable)
		float SetCurPhyAttack(float NewAttack) { return FCurPropertyDetail.PhyAttack = NewAttack; }
	UFUNCTION(BlueprintCallable)
		float SetBaseMagAttack(float NewAttack) { return FBasePropertyDetail.MagAttack = NewAttack; }
	UFUNCTION(BlueprintCallable)
		float SetCurMagAttack(float NewAttack) { return FCurPropertyDetail.MagAttack = NewAttack; }
	UFUNCTION(BlueprintCallable)
		float AddBasePhyAttack(float DeltaAttack) { return FBasePropertyDetail.PhyAttack += DeltaAttack; }
	UFUNCTION(BlueprintCallable)
		float AddCurPhyAttack(float DeltaAttack) { return FCurPropertyDetail.PhyAttack += DeltaAttack; }
	UFUNCTION(BlueprintCallable)
		float AddBaseMagAttack(float DeltaAttack) { return FBasePropertyDetail.MagAttack += DeltaAttack; }
	UFUNCTION(BlueprintCallable)
		float AddCurMagAttack(float DeltaAttack) { return FCurPropertyDetail.MagAttack += DeltaAttack; }
	UFUNCTION(BlueprintCallable)
		float GetBasePhyDef() { return FBasePropertyDetail.PhyDef; }
	UFUNCTION(BlueprintCallable)
		float GetCurPhyDef() { return FCurPropertyDetail.PhyDef; }
	UFUNCTION(BlueprintCallable)
		float GetBaseMagDef() { return FBasePropertyDetail.MagDef; }
	UFUNCTION(BlueprintCallable)
		float GetCurMagDef() { return FCurPropertyDetail.MagDef; }
	UFUNCTION(BlueprintCallable)
		float SetBasePhyDef(float NewDef) { return FBasePropertyDetail.PhyDef = NewDef; }
	UFUNCTION(BlueprintCallable)
		float SetCurPhyDef(float NewDef) { return FCurPropertyDetail.PhyDef = NewDef; }
	UFUNCTION(BlueprintCallable)
		float SetBaseMagDef(float NewDef) { return FBasePropertyDetail.MagDef = NewDef; }
	UFUNCTION(BlueprintCallable)
		float SetCurMagDef(float NewDef) { return FCurPropertyDetail.MagDef = NewDef; }
	UFUNCTION(BlueprintCallable)
		float AddBasePhyDef(float DeltaDef) { return FBasePropertyDetail.PhyDef += DeltaDef; }
	UFUNCTION(BlueprintCallable)
		float AddCurPhyDef(float DeltaDef) { return FCurPropertyDetail.PhyDef += DeltaDef; }
	UFUNCTION(BlueprintCallable)
		float AddBaseMagDef(float DeltaDef) { return FBasePropertyDetail.MagDef += DeltaDef; }
	UFUNCTION(BlueprintCallable)
		float AddCurMagDef(float DeltaDef) { return FCurPropertyDetail.MagDef += DeltaDef; }

	//MoveSpeed and AttackSpeed
	UFUNCTION(BlueprintCallable)
		float GetBaseMoveSpeed() { return FBasePropertyDetail.MoveSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetCurMoveSpeed() { return FCurPropertyDetail.MoveSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetBaseAttackSpeed() { return FBasePropertyDetail.AttackSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetCurAttackSpeed() { return FCurPropertyDetail.AttackSpeed; }
	UFUNCTION(BlueprintCallable)
		float SetBaseMoveSpeed(float NewMoveSpeed) { return FBasePropertyDetail.MoveSpeed = NewMoveSpeed; }
	UFUNCTION(BlueprintCallable)
		float SetCurMoveSpeed(float NewMoveSpeed) { return FCurPropertyDetail.MoveSpeed = NewMoveSpeed; }
	UFUNCTION(BlueprintCallable)
		float SetBaseAttackSpeed(float NewAttackSpeed) { return FBasePropertyDetail.AttackSpeed = NewAttackSpeed; }
	UFUNCTION(BlueprintCallable)
		float SetCurAttackSpeed(float NewAttackSpeed) { return FCurPropertyDetail.AttackSpeed = NewAttackSpeed; }
	UFUNCTION(BlueprintCallable)
		float AddBaseMoveSpeed(float DeltaMoveSpeed) { return FBasePropertyDetail.MoveSpeed += DeltaMoveSpeed; }
	UFUNCTION(BlueprintCallable)
		float AddCurMoveSpeed(float DeltaMoveSpeed) { return FCurPropertyDetail.MoveSpeed += DeltaMoveSpeed; }
	UFUNCTION(BlueprintCallable)
		float AddBaseAttackSpeed(float DeltaAttackSpeed) { return FBasePropertyDetail.AttackSpeed += DeltaAttackSpeed; }
	UFUNCTION(BlueprintCallable)
		float AddCurAttackSpeed(float DeltaAttackSpeed) { return FCurPropertyDetail.AttackSpeed += DeltaAttackSpeed; }
	UFUNCTION(BlueprintCallable)
		void ResetCurProperty();
	UFUNCTION(BlueprintCallable)
		bool IsAlive() { return bIsAlive; }
	UFUNCTION(BlueprintCallable)
		float GetAlttackRange() { return FBasePropertyDetail.AttackRange; }
	UFUNCTION(BlueprintCallable)
		float GetAlttackedRange() { return FBasePropertyDetail.AttackedRange; }
		void  HPRecovering(float DeltaTime);
		void MPRecovering(float DeltaTime);
		int32 SetAlive(int32 UnkonwStatus) { return bIsAlive = UnkonwStatus; }



private:
	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
		FBaseProperty FBasePropertyDetail;
	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
		FCurProperty FCurPropertyDetail;
	uint32 bIsLevelUp : 1;
	const int32 MaxLevel = 16;
	int32 bIsAlive : 1;
};