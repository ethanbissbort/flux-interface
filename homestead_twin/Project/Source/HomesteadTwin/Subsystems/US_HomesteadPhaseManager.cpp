// Copyright Fluxology. All Rights Reserved.

#include "US_HomesteadPhaseManager.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

UUS_HomesteadPhaseManager::UUS_HomesteadPhaseManager()
{
	CurrentPhase = EHomesteadPhase::Phase0;
}

void UUS_HomesteadPhaseManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// TODO: Load phase definitions from data table if available
}

void UUS_HomesteadPhaseManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUS_HomesteadPhaseManager::SetCurrentPhase(EHomesteadPhase NewPhase)
{
	if (CurrentPhase == NewPhase)
	{
		return;
	}

	EHomesteadPhase OldPhase = CurrentPhase;
	CurrentPhase = NewPhase;

	ApplyPhaseVisibility();
	UpdateLevelStreaming();

	OnPhaseChanged(OldPhase, NewPhase);
}

FPhaseDefinition UUS_HomesteadPhaseManager::GetPhaseDefinition(EHomesteadPhase Phase) const
{
	for (const FPhaseDefinition& PhaseDef : PhaseDefinitions)
	{
		if (PhaseDef.Phase == Phase)
		{
			return PhaseDef;
		}
	}
	return FPhaseDefinition();
}

bool UUS_HomesteadPhaseManager::IsObjectVisibleInCurrentPhase(FName ObjectTag) const
{
	FPhaseDefinition CurrentPhaseDef = GetPhaseDefinition(CurrentPhase);
	return CurrentPhaseDef.VisibleObjectTags.Contains(ObjectTag);
}

void UUS_HomesteadPhaseManager::ApplyPhaseVisibility()
{
	// TODO: Iterate through world actors and apply visibility based on phase tags
}

void UUS_HomesteadPhaseManager::UpdateLevelStreaming()
{
	// TODO: Stream in/out levels based on current phase
}
