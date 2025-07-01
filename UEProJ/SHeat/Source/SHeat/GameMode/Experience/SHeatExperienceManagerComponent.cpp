// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Experience/SHeatExperienceManagerComponent.h"

#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"
#include "SHeatExperienceActionSet.h"
#include "SHeatExperienceDefinition.h"
#include "Engine/AssetManager.h"

#pragma region Set Load Experience

void USHeatExperienceManagerComponent::SetCurrentExperience(FPrimaryAssetId ExperienceId)
{
	UAssetManager& AssetManager = UAssetManager::Get();
	FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
	TSubclassOf<USHeatExperienceDefinition> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	check(AssetClass);
	
	const USHeatExperienceDefinition* Experience = GetDefault<USHeatExperienceDefinition>(AssetClass);
	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	CurrentExperience = Experience;
	StartExperienceLoad();
}

void USHeatExperienceManagerComponent::StartExperienceLoad()
{
	check(CurrentExperience != nullptr);
	UAssetManager& AssetManager = UAssetManager::Get();
	
	// TSet<FPrimaryAssetId> BundleAssetList;
	// BundleAssetList.Add(CurrentExperience->GetPrimaryAssetId());
	//
	// for (const TObjectPtr<USHeatExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	// {
	// 	if (ActionSet != nullptr)
	// 	{
	// 		BundleAssetList.Add(ActionSet->GetPrimaryAssetId());
	// 	}
	// }
	// TArray<FName> BundlesToLoad;
	//TODO:BundlesToLoad可能需要加载对应BundleName,这里先不处理
	// TSharedPtr<FStreamableHandle> BundleLoadHandle = nullptr;
	// if (BundleAssetList.Num() > 0)
	// {
	// 	BundleLoadHandle = AssetManager.ChangeBundleStateForPrimaryAssets(BundleAssetList.Array(), BundlesToLoad, {}, false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority);
	// }
	//
	// TSharedPtr<FStreamableHandle> Handle = nullptr;
	OnExperienceLoadComplete();
}

void USHeatExperienceManagerComponent::OnExperienceLoadComplete()
{
	//TODO:先不启用GF玩法,只用Action

	// Execute the actions 只在当前场景激活Action
	FGameFeatureActivatingContext Context;
	const FWorldContext* ExistingWorldContext = GEngine->GetWorldContextFromWorld(GetWorld());
	if (ExistingWorldContext)
	{
		Context.SetRequiredWorldContextHandle(ExistingWorldContext->ContextHandle);
	}
	
	auto ActivateListOfActions = [&Context](const TArray<UGameFeatureAction*>& ActionList)
	{
		for (UGameFeatureAction* Action : ActionList)
		{
			if (Action != nullptr)
			{
				//@TODO: The fact that these don't take a world are potentially problematic in client-server PIE
				// The current behavior matches systems like gameplay tags where loading and registering apply to the entire process,
				// but actually applying the results to actors is restricted to a specific world
				Action->OnGameFeatureRegistering();
				Action->OnGameFeatureLoading();
				Action->OnGameFeatureActivating(Context);
			}
		}
	};

	ActivateListOfActions(CurrentExperience->Actions);
	for (const TObjectPtr<USHeatExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	{
		if (ActionSet != nullptr)
		{
			ActivateListOfActions(ActionSet->Actions);
		}
	}
	
	OnExperienceLoaded.Broadcast(CurrentExperience);
	OnExperienceLoaded.Clear();
}



#pragma endregion

void USHeatExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnSHeatExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}

bool USHeatExperienceManagerComponent::IsExperienceLoaded() const
{
	return CurrentExperience != nullptr;
}

const USHeatExperienceDefinition* USHeatExperienceManagerComponent::GetCurrentExperienceChecked() const
{
	check(CurrentExperience != nullptr);
	return CurrentExperience;
}
