// Copyright Fluxology. All Rights Reserved.

#include "PC_VR.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"

APC_VR::APC_VR()
{
	bUseTeleportLocomotion = true;
	bEnableVignette = true;
	bEnableSnapTurning = true;
	SnapTurnAngle = 45.0f;
	FocusedObject = nullptr;
	LaserPointerDistance = 1000.0f; // 10 meters
}

void APC_VR::BeginPlay()
{
	Super::BeginPlay();
}

void APC_VR::SetupInputComponent()
{
	Super::SetupInputComponent();

	// TODO: Bind VR input actions when using Enhanced Input system
}

void APC_VR::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Update focused object via laser pointer
	AActor* NewFocusedObject = PerformLaserPointerRaycast(true, LaserPointerDistance);

	if (NewFocusedObject != FocusedObject)
	{
		// TODO: Handle focus changed (call component events)
		FocusedObject = NewFocusedObject;
	}
}

void APC_VR::ToggleLocomotionMode()
{
	bUseTeleportLocomotion = !bUseTeleportLocomotion;
}

AActor* APC_VR::PerformLaserPointerRaycast(bool bUseRightHand, float MaxDistance)
{
	// TODO: Get motion controller position and perform raycast from it
	// For now, return nullptr
	return nullptr;
}
