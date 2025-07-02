// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SHeatExperienceDefinition.generated.h"

class USHeatExperienceActionSet;
class UGameFeatureAction;
class USHeatPawnData;
/**
 * 
 */
UCLASS(BlueprintType)
class SHEAT_API USHeatExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:
	// // List of Game Feature Plugins this experience wants to have active
	// UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	// TArray<FString> GameFeaturesToEnable;

	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TObjectPtr<const USHeatPawnData> DefaultPawnData;

	UPROPERTY(EditDefaultsOnly, Instanced, Category="Actions")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;

	// List of additional action sets to compose into this experience
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TArray<TObjectPtr<USHeatExperienceActionSet>> ActionSets;
};
