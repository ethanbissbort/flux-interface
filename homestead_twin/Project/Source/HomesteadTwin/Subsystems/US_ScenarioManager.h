// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "US_ScenarioManager.generated.h"

/**
 * FScenarioDefinition
 *
 * Data structure defining a scenario simulation.
 */
USTRUCT(BlueprintType)
struct FScenarioDefinition
{
	GENERATED_BODY()

	/** Unique scenario ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FName ScenarioId;

	/** Human-readable scenario name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FString ScenarioName;

	/** Scenario description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FString Description;

	/** Category/tags for organization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	TArray<FName> Tags;

	/** Affected object IDs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	TArray<FName> AffectedObjects;

	/** Related SOPs to highlight */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	TArray<FName> RelatedSOPs;

	FScenarioDefinition()
		: ScenarioId(NAME_None)
		, ScenarioName(TEXT(""))
		, Description(TEXT(""))
	{}
};

/**
 * UUS_ScenarioManager
 *
 * Game Instance Subsystem for managing scenario simulations. (FUTURE PHASE F)
 *
 * Responsibilities:
 * - Define and trigger scenario simulations
 * - Apply visual effects to affected objects
 * - Highlight relevant SOPs and systems
 * - Reset to normal state after scenario
 * - Track scenario execution for training
 *
 * Implementation Notes:
 * - Scenarios are visual planning tools, not full physics sims
 * - Examples: power failure, intrusion, fire response
 * - Visual effects: coverage cones, color overlays, pathing arrows
 * - Scenario state can be saved for training review
 */
UCLASS()
class HOMESTEADTWIN_API UUS_ScenarioManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUS_ScenarioManager();

	// Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface

	/** Activate a scenario by ID */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Scenario")
	bool ActivateScenario(FName ScenarioId);

	/** Deactivate the current scenario and reset */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Scenario")
	void DeactivateScenario();

	/** Get the currently active scenario (if any) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Scenario")
	FScenarioDefinition GetActiveScenario(bool& bIsActive) const;

	/** Get scenario definition by ID */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Scenario")
	FScenarioDefinition GetScenarioDefinition(FName ScenarioId) const;

	/** Get all scenario definitions */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Scenario")
	TArray<FScenarioDefinition> GetAllScenarios() const;

	/** Get scenarios by tag */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Scenario")
	TArray<FScenarioDefinition> GetScenariosByTag(FName Tag) const;

	/** Check if a scenario is currently active */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Scenario")
	bool IsScenarioActive() const { return bScenarioActive; }

protected:
	/** Called when a scenario is activated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Scenario")
	void OnScenarioActivated(const FScenarioDefinition& Scenario);

	/** Called when a scenario is deactivated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Scenario")
	void OnScenarioDeactivated();

	/** Apply scenario visual effects to world */
	void ApplyScenarioEffects(const FScenarioDefinition& Scenario);

	/** Reset all scenario effects */
	void ResetScenarioEffects();

protected:
	/** Scenario definitions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Scenario")
	TArray<FScenarioDefinition> ScenarioDefinitions;

	/** Data table containing scenario definitions (optional) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Scenario")
	class UDataTable* ScenarioDataTable;

	/** Currently active scenario ID */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Scenario")
	FName ActiveScenarioId;

	/** Is a scenario currently active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Scenario")
	bool bScenarioActive;
};
