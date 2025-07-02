// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SHeatGameState.h"

#include "Experience/SHeatExperienceManagerComponent.h"

ASHeatGameState::ASHeatGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ExperienceManagerComponent = CreateDefaultSubobject<USHeatExperienceManagerComponent>(TEXT("ExperienceManager"));
}
