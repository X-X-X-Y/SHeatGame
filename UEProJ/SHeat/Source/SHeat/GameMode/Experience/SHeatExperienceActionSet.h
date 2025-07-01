// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SHeatExperienceActionSet.generated.h"

class UGameFeatureAction;
/**
 * 
 */
UCLASS()
class SHEAT_API USHeatExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// List of actions to perform as this experience is loaded/activated/deactivated/unloaded
	UPROPERTY(EditAnywhere, Instanced, Category="Actions to Perform")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
