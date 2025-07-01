// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "SHeatPawnExtensionComponent.generated.h"

class USHeatPawnData;


UCLASS()
class SHEAT_API USHeatPawnExtensionComponent : public UPawnComponent
{
	GENERATED_BODY()

public:

	void SetPawnData(const USHeatPawnData* InPawnData);
	
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	UFUNCTION(BlueprintPure, Category = "SHeat|Pawn")
	static USHeatPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor)
	{
		return (Actor ? Actor->FindComponentByClass<USHeatPawnExtensionComponent>() : nullptr);
	}

protected:
	/** Pawn data used to create the pawn. Specified from a spawn function or on a placed instance. */
	UPROPERTY(EditInstanceOnly, Category = "SHeat|Pawn")
	TObjectPtr<const USHeatPawnData> PawnData;
};
