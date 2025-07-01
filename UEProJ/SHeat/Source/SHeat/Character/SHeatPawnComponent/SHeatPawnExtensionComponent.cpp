// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SHeatPawnComponent/SHeatPawnExtensionComponent.h"

#include "SHUtil/SHeatLogChannels.h"


void USHeatPawnExtensionComponent::SetPawnData(const USHeatPawnData* InPawnData)
{
	check(InPawnData);
	APawn* Pawn = GetPawnChecked<APawn>();
	if (PawnData)
	{
		// UE_LOG(LogSHeat, Error, TEXT("Trying to set PawnData [%s] on pawn [%s] that already has valid PawnData [%s]."),
		//        *GetNameSafe(InPawnData), *GetNameSafe(Pawn), *GetNameSafe(PawnData.Get()));
		return;
	}

	PawnData = InPawnData;
}
