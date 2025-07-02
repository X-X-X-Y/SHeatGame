// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/SHeatInputConfig.h"

#include "SHUtil/SHeatLogChannels.h"

const UInputAction* USHeatInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag,
                                                                   bool bLogNotFound) const
{
	for (const FSHeatInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogSHeat, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* USHeatInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FSHeatInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogSHeat, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
