// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "SHeatExperienceManagerComponent.generated.h"


class USHeatExperienceDefinition;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSHeatExperienceLoaded, const USHeatExperienceDefinition* /*Experience*/);

UCLASS()
class SHEAT_API USHeatExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	void SetCurrentExperience(FPrimaryAssetId ExperienceId);
	void CallOrRegister_OnExperienceLoaded(FOnSHeatExperienceLoaded::FDelegate&& Delegate);
	bool IsExperienceLoaded() const;
	const USHeatExperienceDefinition* GetCurrentExperienceChecked() const;
	
private:
	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	
	
private:
	TObjectPtr<const USHeatExperienceDefinition> CurrentExperience;
	FOnSHeatExperienceLoaded OnExperienceLoaded;
};
