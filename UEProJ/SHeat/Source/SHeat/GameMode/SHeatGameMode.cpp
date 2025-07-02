// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SHeatGameMode.h"

#include "SHeatGameState.h"
#include "SHeatWorldSetting.h"
#include "Character/SHeatCharacter.h"
#include "Character/SHeatPawnData.h"
#include "Character/SHeatPawnComponent/SHeatPawnExtensionComponent.h"
#include "Experience/SHeatExperienceDefinition.h"
#include "Experience/SHeatExperienceManagerComponent.h"
#include "Player/SHeatPlayerController.h"
#include "Player/SHeatPlayerState.h"
#include "SHUtil/SHeatLogChannels.h"


ASHeatGameMode::ASHeatGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ASHeatGameState::StaticClass();
	// GameSessionClass = ALyraGameSession::StaticClass();
	PlayerControllerClass = ASHeatPlayerController::StaticClass();
	// ReplaySpectatorPlayerControllerClass = ALyraReplayPlayerController::StaticClass();
	PlayerStateClass = ASHeatPlayerState::StaticClass();
	DefaultPawnClass = ASHeatCharacter::StaticClass();
	// HUDClass = ALyraHUD::StaticClass();
}



#pragma region GameMode Base Interface Functions

void ASHeatGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Wait for the next frame to give time to initialize startup settings
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ASHeatGameMode::InitGameState()
{
	Super::InitGameState();

	USHeatExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<USHeatExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnSHeatExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

UClass* ASHeatGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const USHeatPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}
	
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

APawn* ASHeatGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
	const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (USHeatPawnExtensionComponent* PawnExtComp = USHeatPawnExtensionComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const USHeatPawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					PawnExtComp->SetPawnData(PawnData);
				}
				else
				{
					UE_LOG(LogSHeat, Error, TEXT("Game mode was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(SpawnedPawn));
				}
			}

			SpawnedPawn->FinishSpawning(SpawnTransform);

			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogSHeat, Error, TEXT("Game mode was unable to spawn Pawn of class [%s] at [%s]."), *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
		}
	}
	else
	{
		UE_LOG(LogSHeat, Error, TEXT("Game mode was unable to spawn Pawn due to NULL pawn class."));
	}

	return nullptr;
}

void ASHeatGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	check(GameState);
	USHeatExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<USHeatExperienceManagerComponent>();
	check(ExperienceComponent);
	if (ExperienceComponent->IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

#pragma endregion

#pragma region Experience

void ASHeatGameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	// Only world settings has a default experience
	if (FPrimaryAssetId ExperienceId; !ExperienceId.IsValid())
	{
		if (ASHeatWorldSetting* SHWordSetting = Cast<ASHeatWorldSetting>(GetWorldSettings()))
		{
			ExperienceId = SHWordSetting->GetDefaultGameplayExperience();
			USHeatExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<USHeatExperienceManagerComponent>();
			check(ExperienceComponent);
			ExperienceComponent->SetCurrentExperience(ExperienceId);
		}
	}
}

void ASHeatGameMode::OnExperienceLoaded(const USHeatExperienceDefinition* CurrentExperience)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (APlayerController* PC = Cast<APlayerController>(*Iterator); (PC != nullptr) && (PC->GetPawn() == nullptr))
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
}

#pragma endregion

#pragma region SHeatGameMode Public Functions

const USHeatPawnData* ASHeatGameMode::GetPawnDataForController(const AController* InController) const
{
	if (InController != nullptr)
	{
		if (const ASHeatPlayerState* SHeatPS = InController->GetPlayerState<ASHeatPlayerState>())
		{
			if (const USHeatPawnData* PawnData = SHeatPS->GetPawnData<USHeatPawnData>())
			{
				return PawnData;
			}
		}
	}

	check(GameState);
	USHeatExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<USHeatExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		const USHeatExperienceDefinition* Experience = ExperienceComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData != nullptr)
		{
			return Experience->DefaultPawnData;
		}
	}
	
	return nullptr;
}

#pragma endregion

