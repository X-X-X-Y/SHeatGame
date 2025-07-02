// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SHeatCharacter.h"

#include "SHeatPawnComponent/SHeatHeroComponent.h"
#include "SHeatPawnComponent/SHeatPawnExtensionComponent.h"

ASHeatCharacter::ASHeatCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PawnExtensionComponent = CreateDefaultSubobject<USHeatPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
}



void ASHeatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (USHeatHeroComponent* HeroComponent = GetComponentByClass<USHeatHeroComponent>())
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}
