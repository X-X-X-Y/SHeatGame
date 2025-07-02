// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SHeatInputConfig.h"
#include "SHeatInputComponent.generated.h"


class USHeatInputConfig;

UCLASS()
class SHEAT_API USHeatInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

	public:
	
	template<class UserClass, typename FuncType>
	void BindNativeAction(const USHeatInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const USHeatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);
};

template <class UserClass, typename FuncType>
void USHeatInputComponent::BindNativeAction(const USHeatInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void USHeatInputComponent::BindAbilityActions(const USHeatInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	check(InputConfig);
	for (const FSHeatInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag).GetHandle());
			}
	
			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle());
			}
		}
	}
}

