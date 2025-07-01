// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "SHeatGameMode.generated.h"

class USHeatPawnData;
class USHeatExperienceDefinition;
/**
 * 
 */
UCLASS()
class SHEAT_API ASHeatGameMode : public AModularGameModeBase
{
	GENERATED_BODY()

public:

	ASHeatGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	//~End of AGameModeBase interface

	UFUNCTION(BlueprintCallable, Category = "Lyra|Pawn")
	const USHeatPawnData* GetPawnDataForController(const AController* InController) const;

protected:

	//Experience
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnExperienceLoaded(const USHeatExperienceDefinition* CurrentExperience);
};
