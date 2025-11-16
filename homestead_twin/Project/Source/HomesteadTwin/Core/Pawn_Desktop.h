// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_Desktop.generated.h"

class UCameraComponent;
class UFloatingPawnMovement;

/**
 * APawn_Desktop
 *
 * First-person pawn for desktop (non-VR) navigation.
 *
 * Responsibilities:
 * - First-person camera setup
 * - WASD movement with sprint/slow walk
 * - Mouse look control
 * - Free-fly mode support (for screenshots and overview)
 *
 * Implementation Notes:
 * - Default movement: walking on ground plane
 * - Sprint: Shift key (increase movement speed)
 * - Slow walk: Ctrl key (decrease movement speed for precision)
 * - Free-fly mode: toggle gravity/collision for god mode navigation
 */
UCLASS()
class HOMESTEADTWIN_API APawn_Desktop : public APawn
{
	GENERATED_BODY()

public:
	APawn_Desktop();

	// Begin APawn Interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End APawn Interface

protected:
	/** Handle forward/backward movement */
	void MoveForward(float Value);

	/** Handle right/left movement */
	void MoveRight(float Value);

	/** Handle up/down movement (free-fly mode only) */
	void MoveUp(float Value);

	/** Handle mouse look pitch */
	void LookUp(float Value);

	/** Handle mouse look yaw */
	void Turn(float Value);

	/** Toggle sprint mode */
	void StartSprint();
	void StopSprint();

	/** Toggle slow walk mode */
	void StartSlowWalk();
	void StopSlowWalk();

public:
	/** Enable/disable free-fly mode */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Movement")
	void SetFreeFlyMode(bool bEnabled);

	/** Check if free-fly mode is active */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Movement")
	bool IsFreeFlyMode() const { return bFreeFlyMode; }

	/** Get current movement speed */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Movement")
	float GetCurrentMovementSpeed() const;

protected:
	/** Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Camera")
	UCameraComponent* CameraComponent;

	/** Movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Movement")
	UFloatingPawnMovement* MovementComponent;

	/** Is free-fly mode active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Movement")
	bool bFreeFlyMode;

	/** Is sprint mode active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Movement")
	bool bIsSprinting;

	/** Is slow walk mode active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Movement")
	bool bIsSlowWalking;

	/** Base movement speed (cm/s) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Movement")
	float BaseMovementSpeed;

	/** Sprint multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Movement")
	float SprintMultiplier;

	/** Slow walk multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Movement")
	float SlowWalkMultiplier;

	/** Mouse sensitivity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Camera")
	float MouseSensitivity;
};
