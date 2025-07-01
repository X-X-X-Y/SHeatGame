// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SHeatPawnData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "SHeat Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class SHEAT_API USHeatPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	USHeatPawnData(const FObjectInitializer& ObjectInitializer);
	
public:

	// Class to instantiate for this pawn (should usually derive from ALyraPawn or ALyraCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Pawn")
	TSubclassOf<APawn> PawnClass;
};
