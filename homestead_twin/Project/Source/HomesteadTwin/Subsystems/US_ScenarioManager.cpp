// Copyright Fluxology. All Rights Reserved.

#include "US_ScenarioManager.h"

UUS_ScenarioManager::UUS_ScenarioManager()
{
	bScenarioActive = false;
	ActiveScenarioId = NAME_None;
}

void UUS_ScenarioManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// TODO: Load scenario definitions from data table if available
}

void UUS_ScenarioManager::Deinitialize()
{
	// Deactivate any active scenario before shutdown
	if (bScenarioActive)
	{
		DeactivateScenario();
	}

	Super::Deinitialize();
}

bool UUS_ScenarioManager::ActivateScenario(FName ScenarioId)
{
	// Deactivate current scenario if any
	if (bScenarioActive)
	{
		DeactivateScenario();
	}

	FScenarioDefinition ScenarioDef = GetScenarioDefinition(ScenarioId);
	if (ScenarioDef.ScenarioId == NAME_None)
	{
		return false;
	}

	ActiveScenarioId = ScenarioId;
	bScenarioActive = true;

	ApplyScenarioEffects(ScenarioDef);
	OnScenarioActivated(ScenarioDef);

	return true;
}

void UUS_ScenarioManager::DeactivateScenario()
{
	if (!bScenarioActive)
	{
		return;
	}

	ResetScenarioEffects();

	ActiveScenarioId = NAME_None;
	bScenarioActive = false;

	OnScenarioDeactivated();
}

FScenarioDefinition UUS_ScenarioManager::GetActiveScenario(bool& bIsActive) const
{
	bIsActive = bScenarioActive;
	if (bScenarioActive)
	{
		return GetScenarioDefinition(ActiveScenarioId);
	}
	return FScenarioDefinition();
}

FScenarioDefinition UUS_ScenarioManager::GetScenarioDefinition(FName ScenarioId) const
{
	for (const FScenarioDefinition& Scenario : ScenarioDefinitions)
	{
		if (Scenario.ScenarioId == ScenarioId)
		{
			return Scenario;
		}
	}
	return FScenarioDefinition();
}

TArray<FScenarioDefinition> UUS_ScenarioManager::GetAllScenarios() const
{
	return ScenarioDefinitions;
}

TArray<FScenarioDefinition> UUS_ScenarioManager::GetScenariosByTag(FName Tag) const
{
	TArray<FScenarioDefinition> Results;
	for (const FScenarioDefinition& Scenario : ScenarioDefinitions)
	{
		if (Scenario.Tags.Contains(Tag))
		{
			Results.Add(Scenario);
		}
	}
	return Results;
}

void UUS_ScenarioManager::ApplyScenarioEffects(const FScenarioDefinition& Scenario)
{
	// TODO: Apply visual effects to affected objects
	// - Color overlays
	// - Coverage cones
	// - Highlight related SOPs
}

void UUS_ScenarioManager::ResetScenarioEffects()
{
	// TODO: Remove all scenario visual effects from world
}
