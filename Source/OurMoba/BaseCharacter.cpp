// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "MobaController.h"
#include"Animiation.h"
#include "CharacterProperty.h"
#include"Kismet\GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ComboIndex = 0;
	DeathIndex = 0;
	bIsAttacking = false;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(105.0f, 240.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; 
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = true; 

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	PrimaryActorTick.bStartWithTickEnabled = true;

	AnimiationComp = CreateDefaultSubobject<UAnimiation>(TEXT("AnimiationComp"));

	PropertyComp = CreateDefaultSubobject<UCharacterProperty>(TEXT("PropertyComp"));
	PropertyComp->SetAlive(true);

	CampComp = CreateDefaultSubobject<UCreatureCamp>(TEXT("CampComp"));
                                                            

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetMoveSpeed(PropertyComp->GetBaseMoveSpeed());
}

void ABaseCharacter::OnSetAttackPressed()
{
	if (bIsAttacking)
	{
		bIsReadyToCombo = true;
	}
	else
	{
		bIsAttacking = true;
		PlayNextMontage(AnimiationComp->AttackAnim,ComboIndex,true);
	}
}
// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CursorToWorld != nullptr) {
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}	
}
// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::OnSetAttackPressed);

}

void ABaseCharacter::CRoleComboAttack(int32 NextIndex)
{
	if (bIsReadyToCombo)
	{
		bIsReadyToCombo = false;
		PlayNextMontage( AnimiationComp->AttackAnim,ComboIndex,true);
	 }
}

void ABaseCharacter::CRoleResetAttack()
{
	bIsAttacking = false;
	bIsReadyToCombo = false;
	ComboIndex = 0;
}
TArray<ABaseCharacter*> ABaseCharacter::GetAllEnemysInRadius(float Radius)
{
	TArray<AActor*> AllActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::GetClass(), AllActor);
	TArray<ABaseCharacter*> AllEnemysInRadius;
	for (int32 i = 0; i < AllActor.Num(); ++i)
	{
		ABaseCharacter* UnknowCharacter = Cast<ABaseCharacter>(AllActor[i]);
		if (UnknowCharacter&&CampComp->CheckIsEnemy(UnknowCharacter->CampComp->GetCamp()))
		{
			if (GetDistanceTo(UnknowCharacter) < Radius) AllEnemysInRadius.Push(UnknowCharacter);
		}
	}
	return AllEnemysInRadius;
}
void ABaseCharacter::PlayNextMontage(TArray<UAnimMontage*> Arr,int32& Index,int32 bisCombo=false)
{
	if (Arr.Num()&&PropertyComp->IsAlive())
	{
		if (Index >= Arr.Num()) Index = 0;
		if (bisCombo)
		{
			PlayAnimMontage(Arr[Index++], PropertyComp->GetCurAttackSpeed());
		}
		else
		{
			PlayAnimMontage(Arr[Index++]);
		}
	}
}
void ABaseCharacter::ReceivePhyDamage(float PhyDamage)
{
	float PhyDef =PropertyComp->GetCurPhyDef();
	float DamageResistance = 0.06*PhyDef / (1 + 0.06*PhyDef);
	float CurDamage = (1 - DamageResistance)*PhyDamage;
	PropertyComp->AddCurHP(-CurDamage);
	CheckIsDead();
}

void ABaseCharacter::ReceiveMagDamage(float MagDamage)
{
	float MagDef = PropertyComp->GetCurMagDef();
	float DamageResistance = MagDef;
	float CurDamage = (1 - DamageResistance)*MagDamage;
	PropertyComp->AddCurHP(-CurDamage);
	CheckIsDead();
}

void ABaseCharacter::CPhyTraceDetect(TArray<FHitResult> HitResult)
{
	TArray<AActor*> Ignored;

		float Damage =PropertyComp->GetCurPhyAttack();
		for (int32 i = 0; i < HitResult.Num(); ++i)
		{
			if (Ignored.Contains(HitResult[i].Actor)) continue;
			ABaseCharacter* Receiver = Cast<ABaseCharacter>(HitResult[i].Actor);
			if (Receiver&&Receiver->PropertyComp->IsAlive())
			{
				Receiver->ReceivePhyDamage(Damage);
				DEBUGprint(Receiver->PropertyComp->GetCurHP());
			}
		}
}

void ABaseCharacter::CMagTraceDetect(TArray<FHitResult> HitResult)
{
	TArray<AActor*> Ignored;

	float Damage = PropertyComp->GetCurMagAttack();
	for (int32 i = 0; i < HitResult.Num(); ++i)
	{
		if (Ignored.Contains(HitResult[i].Actor)) continue;
		ABaseCharacter* Receiver = Cast<ABaseCharacter>(HitResult[i].Actor);
		if (Receiver&&Receiver->PropertyComp->IsAlive())
		{
			Receiver->ReceiveMagDamage(Damage);
			DEBUGprint(Receiver->PropertyComp->GetCurHP());
		}
	}

}
void ABaseCharacter::CheckIsDead()
{
	if (PropertyComp->GetCurHP() < 0.0001)
	{
		
		AMobaController* MC = Cast<AMobaController>(Controller);
		if (MC)
		{
			MC->SetNewMoveDestination(GetActorLocation());
		}
		DEBUGprint(AnimiationComp->DeathAnim.Num());
		PlayNextMontage(AnimiationComp->DeathAnim, DeathIndex);
		PropertyComp->SetAlive(false);
	}
}

void ABaseCharacter::DeathOver()
{
	Destroy();
}
