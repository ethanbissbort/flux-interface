// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_VR.generated.h"

/**
 * APC_VR
 *
 * Player Controller for VR input mode.
 *
 * Responsibilities:
 * - Handle VR motion controller input
 * - Manage VR HUD and 3D UI interactions
 * - Handle object interaction via laser pointer
 * - Manage VR comfort settings (vignette, snap turning, etc.)
 *
 * Implementation Notes:
 * - Support teleport locomotion (primary) and smooth locomotion (optional)
 * - Laser pointer for UI and object interaction
 * - Comfort settings: vignette during movement, snap turning (45° increments)
 * - Follow VR best practices to minimize nausea
 */
UCLASS()
class HOMESTEADTWIN_API APC_VR : public APlayerController
{
	GENERATED_BODY()

public:
	APC_VR();

	// Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	// End APlayerController Interface

protected:
	/** Called when player presses trigger on motion controller */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|VR Input")
	void OnTriggerPressed(bool bIsRightHand);

	/** Called when player releases trigger on motion controller */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|VR Input")
	void OnTriggerReleased(bool bIsRightHand);

	/** Called when player presses grip on motion controller */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|VR Input")
	void OnGripPressed(bool bIsRightHand);

	/** Toggle between teleport and smooth locomotion */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|VR Locomotion")
	void ToggleLocomotionMode();

	/** Perform laser pointer raycast and return hit object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|VR Interaction")
	AActor* PerformLaserPointerRaycast(bool bUseRightHand = true, float MaxDistance = 1000.0f);

public:
	/** Check if teleport locomotion is enabled (vs smooth) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|VR Locomotion")
	bool IsTeleportLocomotion() const { return bUseTeleportLocomotion; }

	/** Check if vignette effect is enabled during movement */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|VR Comfort")
	bool IsVignetteEnabled() const { return bEnableVignette; }

	/** Check if snap turning is enabled (vs smooth turning) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|VR Comfort")
	bool IsSnapTurningEnabled() const { return bEnableSnapTurning; }

	/** Get the currently focused interactive object (if any) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|VR Interaction")
	AActor* GetFocusedObject() const { return FocusedObject; }

protected:
	/** Use teleport locomotion (true) or smooth locomotion (false) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Locomotion")
	bool bUseTeleportLocomotion;

	/** Enable vignette effect during movement (reduces motion sickness) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Comfort")
	bool bEnableVignette;

	/** Enable snap turning (45° increments) vs smooth turning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Comfort")
	bool bEnableSnapTurning;

	/** Snap turn angle in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Comfort")
	float SnapTurnAngle;

	/** Currently focused interactive object via laser pointer */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|VR Interaction")
	AActor* FocusedObject;

	/** Maximum laser pointer raycast distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Interaction")
	float LaserPointerDistance;
};
