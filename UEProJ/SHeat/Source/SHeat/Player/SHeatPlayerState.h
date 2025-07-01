// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "SHeatPlayerState.generated.h"

class USHeatPawnData;

UCLASS()
class SHEAT_API ASHeatPlayerState : public AModularPlayerState
{
	GENERATED_BODY()

public:
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

protected:
	UPROPERTY()
	TObjectPtr<const USHeatPawnData> PawnData;
};
