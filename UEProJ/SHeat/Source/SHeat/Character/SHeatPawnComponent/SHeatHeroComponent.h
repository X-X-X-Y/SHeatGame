// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "GameplayTagContainer.h"
#include "SHeatHeroComponent.generated.h"


struct FInputActionValue;
class USHeatInputConfig;
class USHeatInputComponent;
class UInputMappingContext;

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class SHEAT_API USHeatHeroComponent : public UPawnComponent
{
	GENERATED_BODY()

public:

	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	virtual void BindSHeatNativeInput(USHeatInputComponent* SHeatInputComp, USHeatInputConfig* InputConfig);
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	//NativeInput
	void Input_Move(const FInputActionValue& InputActionValue);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SHeatGame|Input")
	TObjectPtr<UInputMappingContext> DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SHeatGame|Input")
	bool bTestHeroComp;
};
