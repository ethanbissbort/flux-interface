// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_VR.generated.h"

class UCameraComponent;
class USceneComponent;
class UMotionControllerComponent;
class UStaticMeshComponent;

/**
 * APawn_VR
 *
 * VR pawn with motion controller support.
 *
 * Responsibilities:
 * - VR camera setup (tracks HMD position/rotation)
 * - Motion controller components (left and right hands)
 * - Teleport locomotion implementation
 * - Smooth locomotion implementation (optional)
 * - Laser pointer visualization
 *
 * Implementation Notes:
 * - VR origin: center of play space
 * - Motion controllers: visualize hand positions and laser pointers
 * - Teleport: arc-based teleport with valid/invalid surface indicators
 * - Smooth locomotion: optional, with vignette effect for comfort
 * - Comfort settings managed by PC_VR
 */
UCLASS()
class HOMESTEADTWIN_API APawn_VR : public APawn
{
	GENERATED_BODY()

public:
	APawn_VR();

	// Begin APawn Interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End APawn Interface

protected:
	/** Handle teleport input (thumbstick or touchpad) */
	void HandleTeleportInput(float ForwardValue, float RightValue);

	/** Handle smooth locomotion input */
	void HandleSmoothLocomotionInput(float ForwardValue, float RightValue);

	/** Handle turning input */
	void HandleTurnInput(float Value);

	/** Update laser pointer visualization */
	void UpdateLaserPointer(float DeltaTime);

public:
	/** Execute teleport to target location */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|VR Locomotion")
	void ExecuteTeleport(FVector TargetLocation);

	/** Check if teleport destination is valid */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|VR Locomotion")
	bool IsTeleportDestinationValid(FVector TargetLocation) const;

	/** Show/hide laser pointer */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|VR Interaction")
	void SetLaserPointerVisible(bool bVisible, bool bRightHand = true);

protected:
	/** VR Root (origin of play space) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	USceneComponent* VRRoot;

	/** VR Camera (tracks HMD) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UCameraComponent* VRCamera;

	/** Left motion controller */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UMotionControllerComponent* LeftController;

	/** Right motion controller */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UMotionControllerComponent* RightController;

	/** Left hand mesh (visual representation) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UStaticMeshComponent* LeftHandMesh;

	/** Right hand mesh (visual representation) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UStaticMeshComponent* RightHandMesh;

	/** Left laser pointer mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UStaticMeshComponent* LeftLaserPointer;

	/** Right laser pointer mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|VR")
	UStaticMeshComponent* RightLaserPointer;

	/** Teleport arc visualization component (Blueprint can override) */
	UPROPERTY(BlueprintReadWrite, Category = "Homestead Twin|VR Locomotion")
	USceneComponent* TeleportArcComponent;

	/** Teleport destination marker component (Blueprint can override) */
	UPROPERTY(BlueprintReadWrite, Category = "Homestead Twin|VR Locomotion")
	USceneComponent* TeleportMarkerComponent;

	/** Teleport locomotion speed (arc velocity) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Locomotion")
	float TeleportArcVelocity;

	/** Smooth locomotion speed (cm/s) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Locomotion")
	float SmoothLocomotionSpeed;

	/** Maximum teleport distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR Locomotion")
	float MaxTeleportDistance;
};
