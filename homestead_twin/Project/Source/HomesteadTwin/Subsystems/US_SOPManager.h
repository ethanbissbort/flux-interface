// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "US_SOPManager.generated.h"

/**
 * FSOPStep
 *
 * A single step in a Standard Operating Procedure.
 */
USTRUCT(BlueprintType)
struct FSOPStep
{
	GENERATED_BODY()

	/** Step number (1-based) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	int32 StepNumber;

	/** Step description/instruction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	FString Description;

	/** Optional warning or caution text */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	FString Warning;

	/** Expected duration for this step (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	float EstimatedDuration;
};

/**
 * FStandardOperatingProcedure
 *
 * Data structure defining a complete SOP.
 */
USTRUCT(BlueprintType)
struct FStandardOperatingProcedure
{
	GENERATED_BODY()

	/** Unique SOP identifier (e.g., "SOP_POWER_DOWN_RACK_01") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	FName SOPId;

	/** Human-readable title */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	FString Title;

	/** Description of what this SOP accomplishes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	FString Description;

	/** Object IDs this SOP applies to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	TArray<FName> LinkedObjectIds;

	/** Ordered list of steps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	TArray<FSOPStep> Steps;

	/** Total estimated time for procedure (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	float TotalEstimatedTime;

	/** Tags for categorization (e.g., "power", "fire", "security") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOP")
	TArray<FName> Tags;
};

/**
 * UUS_SOPManager
 *
 * Game Instance Subsystem for managing Standard Operating Procedures.
 *
 * Responsibilities:
 * - Load SOP data from data table or JSON
 * - Query SOPs by ID, linked object, or tag
 * - Provide SOP data to UI widgets and components
 * - Track SOP execution state (optional future feature)
 *
 * Implementation Notes:
 * - SOPs stored in UE Data Table (imported from CSV/JSON)
 * - Query methods support filtering by object, tag, or text search
 * - SOP execution tracking (checklists, timers) is future phase
 */
UCLASS()
class HOMESTEADTWIN_API UUS_SOPManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUS_SOPManager();

	// Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface

	/** Load SOPs from data table */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|SOP")
	void LoadSOPData();

	/** Get SOP by ID */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|SOP")
	FStandardOperatingProcedure GetSOPById(FName SOPId) const;

	/** Get all SOPs linked to a specific object */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|SOP")
	TArray<FStandardOperatingProcedure> GetSOPsForObject(FName ObjectId) const;

	/** Get all SOPs with a specific tag */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|SOP")
	TArray<FStandardOperatingProcedure> GetSOPsByTag(FName Tag) const;

	/** Get all SOPs */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|SOP")
	TArray<FStandardOperatingProcedure> GetAllSOPs() const;

	/** Search SOPs by text (title or description) */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|SOP")
	TArray<FStandardOperatingProcedure> SearchSOPs(const FString& SearchText) const;

protected:
	/** SOP data storage */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|SOP")
	TMap<FName, FStandardOperatingProcedure> SOPDatabase;

	/** Data table containing SOP definitions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|SOP")
	class UDataTable* SOPDataTable;
};
