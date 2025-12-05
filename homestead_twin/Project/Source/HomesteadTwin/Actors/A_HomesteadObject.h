// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_HomesteadObject.generated.h"

class UStaticMeshComponent;
class UU_InteractableComponent;
class UU_SOPComponent;
class UU_TelemetryComponent;

/**
 * AA_HomesteadObject
 *
 * Base actor class for all physical objects in the Homestead Twin.
 *
 * Responsibilities:
 * - Provide consistent metadata (ID, category, description)
 * - Support for interaction, SOPs, and telemetry via components
 * - Phase-based visibility
 * - Spatial alignment to coordinate system
 *
 * Implementation Notes:
 * - All scanned and hand-modeled assets should inherit from this
 * - Components are optional; attach as needed per object type
 * - Use tags for phase visibility and categorization
 */
UCLASS()
class HOMESTEADTWIN_API AA_HomesteadObject : public AActor
{
	GENERATED_BODY()

public:
	AA_HomesteadObject();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End AActor Interface

public:
	/** Get object ID */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	FName GetObjectId() const { return ObjectId; }

	/** Get object category */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	FName GetObjectCategory() const { return Category; }

	/** Get object description */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	FString GetObjectDescription() const { return Description; }

	/** Get interactable component (if exists) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	UU_InteractableComponent* GetInteractableComponent() const { return InteractableComponent; }

	/** Get SOP component (if exists) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	UU_SOPComponent* GetSOPComponent() const { return SOPComponent; }

	/** Get telemetry component (if exists) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	UU_TelemetryComponent* GetTelemetryComponent() const { return TelemetryComponent; }

	/** Check if this object is interactive */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Object")
	bool IsInteractive() const { return InteractableComponent != nullptr; }

protected:
	/** Called when object is initialized */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Object")
	void OnHomesteadObjectInit();

protected:
	/** Visual mesh component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UStaticMeshComponent* VisualMesh;

	/** Interactable component (optional) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UU_InteractableComponent* InteractableComponent;

	/** SOP component (optional) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UU_SOPComponent* SOPComponent;

	/** Telemetry component (optional, future phase) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UU_TelemetryComponent* TelemetryComponent;

	/** Unique object identifier (e.g., "rack_main_42u_01") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Metadata")
	FName ObjectId;

	/** Object category (e.g., "rack", "container", "sensor", "deterrent") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Metadata")
	FName Category;

	/** Human-readable description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Metadata")
	FString Description;

	/** Phase tags for visibility (e.g., "Phase1", "Phase2") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Phase")
	TArray<FName> PhaseTags;

	/** Additional metadata tags */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Metadata")
	TArray<FName> MetadataTags;
};
