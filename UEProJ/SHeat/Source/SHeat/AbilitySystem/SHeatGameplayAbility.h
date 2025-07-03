// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SHeatGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ESHeatAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,
	
	// Continually try to activate the ability while the input is active.
	WhileInputActive
};

UCLASS()
class SHEAT_API USHeatGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SHeat|Ability Activation")
	ESHeatAbilityActivationPolicy ActivationPolicy;
};
