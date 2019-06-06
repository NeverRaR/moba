// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "GhostForm.generated.h"

/**
 * 
 */
UCLASS()
class OURMOBA_API AGhostForm : public ABaseBuff
{
	GENERATED_BODY()
public:
	AGhostForm();
	virtual bool BuffIsEffective(ABaseCharacter* OwnerPawn)override;
};
