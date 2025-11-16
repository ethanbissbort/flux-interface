// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "U_SOPComponent.generated.h"

/**
 * UU_SOPComponent
 *
 * Component that links an actor to Standard Operating Procedures.
 *
 * Responsibilities:
 * - Store list of SOP IDs relevant to this object
 * - Query US_SOPManager for SOP data
 * - Provide SOP data to UI when object is interacted with
 *
 * Implementation Notes:
 * - Attach to AA_HomesteadObject
 * - SOPs are managed by US_SOPManager subsystem
 * - This component just holds the links (SOP IDs)
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOMESTEADTWIN_API UU_SOPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UU_SOPComponent();

	// Begin UActorComponent Interface
	virtual void BeginPlay() override;
	// End UActorComponent Interface

	/** Get all SOP IDs linked to this object */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|SOP")
	TArray<FName> GetLinkedSOPIds() const { return LinkedSOPIds; }

	/** Add a SOP ID to this object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|SOP")
	void AddLinkedSOP(FName SOPId);

	/** Remove a SOP ID from this object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|SOP")
	void RemoveLinkedSOP(FName SOPId);

	/** Check if this object has any SOPs */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|SOP")
	bool HasSOPs() const { return LinkedSOPIds.Num() > 0; }

	/** Get SOPs from US_SOPManager (convenience method) */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|SOP")
	TArray<struct FStandardOperatingProcedure> GetSOPData() const;

protected:
	/** List of SOP IDs linked to this object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|SOP")
	TArray<FName> LinkedSOPIds;
};
