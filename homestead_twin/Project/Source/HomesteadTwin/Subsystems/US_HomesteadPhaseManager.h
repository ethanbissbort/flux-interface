// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "US_HomesteadPhaseManager.generated.h"

/**
 * EHomesteadPhase
 *
 * Enumeration of homestead build-out phases.
 */
UENUM(BlueprintType)
enum class EHomesteadPhase : uint8
{
	Phase0  UMETA(DisplayName = "Phase 0 - Minimal Containers"),
	Phase1  UMETA(DisplayName = "Phase 1 - Workshop & Rack"),
	Phase2  UMETA(DisplayName = "Phase 2 - Tiny Home & Orchard"),
	Phase3  UMETA(DisplayName = "Phase 3 - Greenhouse & Swales"),
	Phase4  UMETA(DisplayName = "Phase 4 - Perimeter & Deterrence"),
	Phase5  UMETA(DisplayName = "Phase 5 - Full Build-out"),
	MAX     UMETA(Hidden)
};

/**
 * FPhaseDefinition
 *
 * Data structure defining a single homestead phase.
 */
USTRUCT(BlueprintType)
struct FPhaseDefinition
{
	GENERATED_BODY()

	/** Phase identifier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	EHomesteadPhase Phase;

	/** Human-readable phase name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	FString PhaseName;

	/** Phase description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	FString Description;

	/** Actors/objects visible in this phase (by tag or ID) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	TArray<FName> VisibleObjectTags;

	/** Sub-levels to stream in for this phase */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	TArray<FName> StreamedLevels;
};

/**
 * UUS_HomesteadPhaseManager
 *
 * Game Instance Subsystem for managing homestead build-out phases (P0-P5).
 *
 * Responsibilities:
 * - Maintain current phase state
 * - Toggle actor visibility based on phase
 * - Stream in/out sub-levels based on phase
 * - Provide phase metadata (names, descriptions)
 * - Persist phase selection across sessions
 *
 * Implementation Notes:
 * - Phase data can be stored in a data table or hardcoded
 * - Phase changes trigger visibility updates for tagged actors
 * - Level streaming is async; wait for completion before notifying UI
 */
UCLASS()
class HOMESTEADTWIN_API UUS_HomesteadPhaseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUS_HomesteadPhaseManager();

	// Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface

	/** Set the current phase */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Phase")
	void SetCurrentPhase(EHomesteadPhase NewPhase);

	/** Get the current phase */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Phase")
	EHomesteadPhase GetCurrentPhase() const { return CurrentPhase; }

	/** Get phase definition by phase enum */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Phase")
	FPhaseDefinition GetPhaseDefinition(EHomesteadPhase Phase) const;

	/** Get all phase definitions */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Phase")
	TArray<FPhaseDefinition> GetAllPhaseDefinitions() const { return PhaseDefinitions; }

	/** Check if an object is visible in the current phase */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Phase")
	bool IsObjectVisibleInCurrentPhase(FName ObjectTag) const;

protected:
	/** Called when phase changes */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Phase")
	void OnPhaseChanged(EHomesteadPhase OldPhase, EHomesteadPhase NewPhase);

	/** Apply phase visibility to all actors in the world */
	void ApplyPhaseVisibility();

	/** Stream in/out levels for the current phase */
	void UpdateLevelStreaming();

protected:
	/** Current phase */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Phase")
	EHomesteadPhase CurrentPhase;

	/** Phase definitions (can be loaded from data table) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Phase")
	TArray<FPhaseDefinition> PhaseDefinitions;

	/** Data table containing phase definitions (optional) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Phase")
	class UDataTable* PhaseDataTable;
};
