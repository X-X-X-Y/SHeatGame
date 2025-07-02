// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SHeatPawnComponent/SHeatHeroComponent.h"

#include "EnhancedInputSubsystems.h"
#include "SHeatPawnExtensionComponent.h"
#include "Character/SHeatPawnData.h"
#include "Input/SHeatInputComponent.h"
#include "Input/SHeatInputConfig.h"
#include "SHUtil/SHeatGameplayTags.h"


#pragma region Player Input

void USHeatHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent)
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	USHeatInputComponent* SHeatInputComp = Cast<USHeatInputComponent>(PlayerInputComponent); 
	if (!SHeatInputComp)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);
	const ULocalPlayer* LP = Cast<ULocalPlayer>(PC->GetLocalPlayer());
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	if (const USHeatPawnExtensionComponent* PawnExtComp = USHeatPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const USHeatPawnData* PawnData = PawnExtComp->GetPawnData<USHeatPawnData>())
		{
			if (USHeatInputConfig* InputConfig = PawnData->InputConfig)
			{
				TArray<uint32> BindHandles;
				SHeatInputComp->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

				//BindNativeInput
				BindSHeatNativeInput(SHeatInputComp, InputConfig);
			}
		}
	}
}

void USHeatHeroComponent::BindSHeatNativeInput(USHeatInputComponent* SHeatInputComp, USHeatInputConfig* InputConfig)
{
	if (bTestHeroComp)
	{
		SHeatInputComp->BindNativeAction(InputConfig, SHeatGameplayTags::InputTag_Native_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	}
}

//Ability Input
void USHeatHeroComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void USHeatHeroComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void USHeatHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;
	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

#pragma endregion


