// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Desktop.generated.h"

/**
 * APC_Desktop
 *
 * Player Controller for desktop (non-VR) input mode.
 *
 * Responsibilities:
 * - Handle keyboard and mouse input
 * - Manage desktop HUD and UI interactions
 * - Handle object interaction (raycast from camera, E key to interact)
 * - Manage free-fly camera mode toggle
 *
 * Implementation Notes:
 * - Input bindings: WASD movement, mouse look, E interact, Shift sprint, Ctrl slow walk
 * - Support for free-fly camera mode (god mode for screenshots/overview)
 * - Cursor visibility toggles for UI interactions
 */
UCLASS()
class HOMESTEADTWIN_API APC_Desktop : public APlayerController
{
	GENERATED_BODY()

public:
	APC_Desktop();

	// Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	// End APlayerController Interface

protected:
	/** Called when player presses interact key (default: E) */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Input")
	void OnInteractPressed();

	/** Called when player presses phase selector key (default: Tab) */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Input")
	void OnPhaseSelectorPressed();

	/** Toggle free-fly camera mode */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Camera")
	void ToggleFreeFlyMode();

	/** Perform interaction raycast and return hit object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Interaction")
	AActor* PerformInteractionRaycast(float MaxDistance = 500.0f);

public:
	/** Check if currently in free-fly camera mode */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Camera")
	bool IsFreeFlyMode() const { return bFreeFlyMode; }

	/** Get the currently focused interactive object (if any) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Interaction")
	AActor* GetFocusedObject() const { return FocusedObject; }

protected:
	/** Is free-fly camera mode active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Camera")
	bool bFreeFlyMode;

	/** Currently focused interactive object */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Interaction")
	AActor* FocusedObject;

	/** Maximum raycast distance for object interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Interaction")
	float InteractionRaycastDistance;

	/** Update rate for interaction raycasts (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Interaction")
	float InteractionUpdateRate;

private:
	/** Timer for interaction raycast updates */
	float InteractionUpdateTimer;
};
