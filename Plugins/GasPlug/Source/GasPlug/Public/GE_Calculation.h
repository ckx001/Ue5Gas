// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectCalculation.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_Calculation.generated.h"

/**
 * 
 */
UCLASS()
class GASPLUG_API UGE_Calculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
public:
	UGE_Calculation();
	
};
