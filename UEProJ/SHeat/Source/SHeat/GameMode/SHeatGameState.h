// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "SHeatGameState.generated.h"

class USHeatExperienceManagerComponent;
/**
 * 
 */
UCLASS()
class SHEAT_API ASHeatGameState : public AModularGameStateBase
{
	GENERATED_BODY()

public:
	ASHeatGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
private:
	UPROPERTY()
	TObjectPtr<USHeatExperienceManagerComponent> ExperienceManagerComponent;
};
