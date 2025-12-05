// Copyright Fluxology. All Rights Reserved.

#include "Pawn_VR.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MotionControllerComponent.h"
#include "Components/InputComponent.h"

APawn_VR::APawn_VR()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create VR root (play space origin)
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	RootComponent = VRRoot;

	// Create VR camera (tracks HMD)
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(VRRoot);

	// Create motion controllers
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(VRRoot);
	LeftController->SetTrackingMotionSource(FName("Left"));

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(VRRoot);
	RightController->SetTrackingMotionSource(FName("Right"));

	// Create hand meshes
	LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftController);

	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightController);

	// Create laser pointer meshes
	LeftLaserPointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLaserPointer"));
	LeftLaserPointer->SetupAttachment(LeftController);
	LeftLaserPointer->SetVisibility(false);

	RightLaserPointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLaserPointer"));
	RightLaserPointer->SetupAttachment(RightController);
	RightLaserPointer->SetVisibility(false);

	// Initialize default values
	TeleportArcComponent = nullptr;
	TeleportMarkerComponent = nullptr;
	TeleportArcVelocity = 900.0f;
	SmoothLocomotionSpeed = 300.0f;
	MaxTeleportDistance = 1000.0f; // 10 meters
}

void APawn_VR::BeginPlay()
{
	Super::BeginPlay();
}

void APawn_VR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLaserPointer(DeltaTime);
}

void APawn_VR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// TODO: Bind VR input actions when using Enhanced Input system
}

void APawn_VR::HandleTeleportInput(float ForwardValue, float RightValue)
{
	// TODO: Calculate teleport arc and show destination marker
}

void APawn_VR::HandleSmoothLocomotionInput(float ForwardValue, float RightValue)
{
	// TODO: Implement smooth locomotion with vignette
}

void APawn_VR::HandleTurnInput(float Value)
{
	// TODO: Implement snap turning or smooth turning
}

void APawn_VR::UpdateLaserPointer(float DeltaTime)
{
	// TODO: Update laser pointer visualization and hit detection
}

void APawn_VR::ExecuteTeleport(FVector TargetLocation)
{
	if (IsTeleportDestinationValid(TargetLocation))
	{
		SetActorLocation(TargetLocation);
	}
}

bool APawn_VR::IsTeleportDestinationValid(FVector TargetLocation) const
{
	// TODO: Check if destination is on valid walkable surface
	// For now, just check if within max distance
	float Distance = FVector::Dist(GetActorLocation(), TargetLocation);
	return Distance <= MaxTeleportDistance;
}

void APawn_VR::SetLaserPointerVisible(bool bVisible, bool bRightHand)
{
	if (bRightHand && RightLaserPointer)
	{
		RightLaserPointer->SetVisibility(bVisible);
	}
	else if (!bRightHand && LeftLaserPointer)
	{
		LeftLaserPointer->SetVisibility(bVisible);
	}
}
