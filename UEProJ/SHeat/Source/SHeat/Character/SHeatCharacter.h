// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "SHeatCharacter.generated.h"

class USHeatPawnExtensionComponent;

UCLASS()
class SHEAT_API ASHeatCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	ASHeatCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SHeat|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USHeatPawnExtensionComponent> PawnExtensionComponent;
};
