// Copyright Fluxology. All Rights Reserved.

#include "U_SOPComponent.h"
#include "Subsystems/US_SOPManager.h"

UU_SOPComponent::UU_SOPComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UU_SOPComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UU_SOPComponent::AddLinkedSOP(FName SOPId)
{
	if (!LinkedSOPIds.Contains(SOPId))
	{
		LinkedSOPIds.Add(SOPId);
	}
}

void UU_SOPComponent::RemoveLinkedSOP(FName SOPId)
{
	LinkedSOPIds.Remove(SOPId);
}

TArray<FStandardOperatingProcedure> UU_SOPComponent::GetSOPData() const
{
	// TODO: Query US_SOPManager subsystem for SOP data
	// For now, return empty array
	return TArray<FStandardOperatingProcedure>();
}
