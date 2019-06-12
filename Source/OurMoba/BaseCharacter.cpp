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
#include"Particles\ParticleSystem.h"
#include "AIManager.h"
#include "OurMobaGameMode.h"
#include"Kismet\KismetSystemLibrary.h"
#include"Components\SkeletalMeshComponent.h"
#include"Buff.h"
#include"BaseBuff.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
	//Is true when the character is Base_Dawn or Base_Dusk
	bIsBase = false;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ComboIndex = 0;
	DeathIndex = 0;
	bIsAttacking = false;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(105.0f, 240.0f);
	GetCapsuleComponent()->SetIsReplicated(true);

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
	TopDownCameraComponent->bUsePawnControlRotation = false;
	TopDownCameraComponent->SetWorldLocation(FVector(-60.0f, -60.0f, 2500.0f));
	TopDownCameraComponent->SetWorldRotation(FRotator(-70.0f, 0.0f, 0.0f));

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(48.0f, 96.0f, 96.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetWorldLocation(FVector(0.0f, 0.0f, -2000.0f));
	PrimaryActorTick.bStartWithTickEnabled = true;

	AnimiationComp = CreateDefaultSubobject<UAnimiation>(TEXT("AnimiationComp"));

	PropertyComp = CreateDefaultSubobject<UCharacterProperty>(TEXT("PropertyComp"));
	PropertyComp->SetAlive(true);

	CampComp = CreateDefaultSubobject<UCreatureCamp>(TEXT("CampComp"));
	
	AIManger= CreateDefaultSubobject<UAIManager>(TEXT("AIManger"));

	BuffComp= CreateDefaultSubobject<UBuff>(TEXT("BuffComp"));
	GetCharacterMovement()->MaxAcceleration = 1000.0f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetMoveSpeed(PropertyComp->GetBaseMoveSpeed());

	NetUpdateFrequency = 120.0f;
	OriginLocation = GetActorLocation();
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
		PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, true);
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
	GetCharacterMovement()->MaxWalkSpeed = PropertyComp->GetCurMoveSpeed();
	/*if (PropertyComp->GetCurHP() > 0 && bIsAttacking == false)
		bCanRecall = true;
	else
		bCanRecall = false;*/
}
// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::OnSetAttackPressed);
	PlayerInputComponent->BindAction("Recall", IE_Pressed, this, &ABaseCharacter::Recall);

}

void ABaseCharacter::CRoleComboAttack(int32 NextIndex)
{
	if (bIsReadyToCombo)
	{
		bIsReadyToCombo = false;
		PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, PropertyComp->GetCurAttackSpeed());
		
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActor);
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

TArray<ABaseCharacter*> ABaseCharacter::GetAllEnemysInRadiusToLocation(float Radius, FVector TargetLocation)
{
	TArray<AActor*> AllActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActor);
	TArray<ABaseCharacter*> AllEnemysInRadius;
	for (int32 i = 0; i < AllActor.Num(); ++i)
	{
		ABaseCharacter* UnknowCharacter = Cast<ABaseCharacter>(AllActor[i]);
		if (UnknowCharacter&&CheckIsEnemy(UnknowCharacter))
		{
			
			FVector EnemyLocaion = AllActor[i]->GetActorLocation();
			FVector Direction = EnemyLocaion - TargetLocation;
			Direction.Z = 0.0f;
			if (Direction .Size()< Radius) AllEnemysInRadius.Push(UnknowCharacter);
		}
	}
	return AllEnemysInRadius;
}

void ABaseCharacter::PlayNextMontage(TArray<UAnimMontage*> Arr, int32& Index, float Rate)
{
	if (Arr.Num() && PropertyComp->IsAlive())
	{
		if (Index >= Arr.Num()) Index = 0;
		float AnimLength = Arr[Index]->SequenceLength;
		if (Role < ROLE_Authority)
		{
			ServerPlayMontage(Arr[Index++], Rate);
			CDelay(0.6*AnimLength);
			return;
		}
		MulticastPlayMontage(Arr[Index++], Rate);
		CDelay(0.6*AnimLength);
	}
}

void ABaseCharacter::DeathEffect(ABaseCharacter * Attacker)
{


}

void ABaseCharacter::AttackEffect(ABaseCharacter * Receiver)
{
	if (Receiver&&Receiver->PropertyComp->IsAlive())
	{
		for (int32 i = 0; i < BuffComp->ReleaseDebuff.Num(); ++i)
		{
			ABaseBuff* Buff = GetWorld()->SpawnActor<ABaseBuff>(BuffComp->ReleaseDebuff[i]->GetClass());
			Buff->Attacker = this;
			Receiver->BuffComp->AddBuff(Buff);
		}
	}
}

void ABaseCharacter::MulticastPlayMontage_Implementation(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	PlayAnimMontage(AnimMontage, InPlayRate);
}

//Play Animation On Server
void ABaseCharacter::ServerPlayMontage_Implementation(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	MulticastPlayMontage(AnimMontage, InPlayRate);
}

bool ABaseCharacter::ServerPlayMontage_Validate(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	return true;
}

float ABaseCharacter::ReceivePhyDamage(float PhyDamage, ABaseCharacter* Attacker)
{
	if (Attacker&&Attacker->PropertyComp->IsAlive())
	{
		if (PhyDamage < 0.0f) return 0.0f;
		float PhyDef = PropertyComp->GetCurPhyDef();
		float DamageResistance = PhyDef / (PhyDef + 150);
		float CurDamage = (1 - DamageResistance)*PhyDamage;
		PropertyComp->AddCurHP(-CurDamage);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitReact, GetActorLocation());
		CheckIsDead(Attacker);
		return CurDamage;
	}
	else return 0.0f;
}

void ABaseCharacter::ReceiveMagDamage(float MagDamage, ABaseCharacter* Attacker)
{
	if (Attacker&&Attacker->PropertyComp->IsAlive())
	{
		if (MagDamage < 0.0f) return;
		float MagDef = PropertyComp->GetCurMagDef();
		float DamageResistance = MagDef / 100;
		float CurDamage = (1 - DamageResistance)*MagDamage;
		PropertyComp->AddCurHP(-CurDamage);
		CheckIsDead(Attacker);
	}
}

void ABaseCharacter::CPhyTraceDetect(TArray<FHitResult> HitResult)
{
	TArray<AActor*> Ignored;

	float Damage = PropertyComp->GetCurPhyAttack();
	for (int32 i = 0; i < HitResult.Num(); ++i)
	{
		if (Ignored.Contains(HitResult[i].GetActor())) continue;
		Ignored.Add(HitResult[i].GetActor());
		ABaseCharacter* Receiver = Cast<ABaseCharacter>(HitResult[i].Actor);
		if (Receiver&&Receiver->PropertyComp->IsAlive())
		{
			if (CheckIsEnemy(Receiver))
			{
				AttackEffect(Receiver);
				float CurDamage=Receiver->ReceivePhyDamage(Damage,this);
				if (PropertyComp->IsAlive())
				{
					PropertyComp->AddCurHP(PropertyComp->GetCurLeech()*CurDamage);
				}
			}
		}
	}
}

void ABaseCharacter::CPhySingleDetect(ABaseCharacter * Target)
{

	float Damage = PropertyComp->GetCurPhyAttack();
	SetFireParticle(FireReact,ComboIndex);
	float CurDamage = Target->ReceivePhyDamage(Damage,this);
	if (PropertyComp->IsAlive())
	{
		PropertyComp->AddCurHP(PropertyComp->GetCurLeech()*CurDamage);
	}

}

void ABaseCharacter::CMagTraceDetect(TArray<FHitResult> HitResult)
{
	TArray<AActor*> Ignored;

	float Damage = PropertyComp->GetCurMagAttack();
	for (int32 i = 0; i < HitResult.Num(); ++i)
	{
		if (Ignored.Contains(HitResult[i].GetActor())) continue;
		Ignored.Add(HitResult[i].GetActor());
		ABaseCharacter* Receiver = Cast<ABaseCharacter>(HitResult[i].Actor);
		if (Receiver&&Receiver->PropertyComp->IsAlive())
		{
			if (CheckIsEnemy(Receiver))
			{
				Receiver->ReceiveMagDamage(Damage,this);
			}
		}
	}

}
void ABaseCharacter::CheckIsDead(ABaseCharacter* Attacker)
{
	if (PropertyComp->GetCurHP() < 0.0001)
	{

		AMobaController* MC = Cast<AMobaController>(Controller);
		if (MC)
		{
			MC->SetNewMoveDestination(GetActorLocation());
		}
		SetActorEnableCollision(false);
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathReact, GetActorLocation());
		PropertyComp->SetAlive(false);
		BuffComp->ClearAllBuff();
		check(BuffComp->UniqueBuff.Num()==0&& BuffComp->MultiBuff.Num() == 0)//检查是否清除buff成功
		if (CampComp->CheckIsHero())
		{
			PropertyComp->AddDeathNum(1);
			PropertyComp->AddCurMP(-99999.0f);
			RebornTime = RebornTime + PropertyComp->GetCurLevel();
			GetWorldTimerManager().SetTimer(TimerHandle1, this, &ABaseCharacter::Reborn, RebornTime, false);
		}
		if (Attacker)
		{
			if (Attacker->CampComp->CheckIsHero())
			{
				if (CampComp->CheckIsHero())
				{
					Attacker->PropertyComp->AddKillNum(1);
				}
				Attacker->PropertyComp->CheckLevelUp(PropertyComp->GetEXPWorth());
				Attacker->PropertyComp->AddMoney(PropertyComp->GetMoneyWorth());
			}
		}
		if (bIsBase)
		{
			AOurMobaGameMode* GM = Cast<AOurMobaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GM) 
			{
				GM->GameOver();
			}
		}
		OnActorDeath.Broadcast(this);
		DeathEffect(Attacker);
		if (CampComp->CheckIsHero())
		{
			GetMesh()->SetVisibility(false);
		}
		else
		{
			Destroy();
		}
	}
}

void ABaseCharacter::DeathOver()
{
	Destroy();
}

void ABaseCharacter::Recall()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::SetRecall, 15.0f, false);
}

void ABaseCharacter::SetRecall()
{
	if (bCanRecall)
	{
		PropertyComp->ResetCurProperty();
		SetActorLocation(OriginLocation);
	}
}

void ABaseCharacter::Reborn()
{
	SetActorEnableCollision(true);
	PropertyComp->SetAlive(true);
	PropertyComp->ResetCurProperty();
	GetMesh()->SetVisibility(true);
	CRoleResetAttack();
	SetActorLocation(OriginLocation);
}

void ABaseCharacter::ClientPlayMontage_Implementation(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	PlayAnimMontage(AnimMontage, InPlayRate);
}
