// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinBlast.h"
#include"Animiation.h"
#include"Kismet/KismetMathLibrary.h"
#include"MobaController.h"
#include"CharacterProperty.h"
void ATwinBlast::OnSetAttackPressed()
{
	if (bIsAttacking)
	{
		bIsReadyToCombo = true;
	}
	else
	{
		TurnToMouseLocation();
		bIsAttacking = true;
		PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, true);
	}
}

void ATwinBlast::CRoleComboAttack(int32 NextIndex)
{
	if (bIsReadyToCombo)
	{
		TurnToMouseLocation();
		bIsReadyToCombo = false;
		PlayNextMontage(AnimiationComp->AttackAnim, ComboIndex, PropertyComp->GetCurAttackSpeed());
	}
}

void ATwinBlast::TurnToMouseLocation()
{

	FVector MouseLocaton = GetMouseLocation();
	FVector OwnerLocation = GetActorLocation();
	FVector DirLocation = GetMouseLocation() - GetActorLocation();
	if (DirLocation.Size())
	{
		DirLocation = TurnCoefficient *DirLocation / (DirLocation.Size());
	}
	AMobaController* MC = Cast<AMobaController>(Controller);
	if (MC)
	{
		MC->SetNewMoveDestination(DirLocation);
	}
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseLocaton).Yaw;
	SetActorRotation(NewRotation);
}

void ATwinBlast::Skill1Release()
{


}
