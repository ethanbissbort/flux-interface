// Copyright Fluxology. All Rights Reserved.

#include "PC_Desktop.h"
#include "Pawn_Desktop.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"

APC_Desktop::APC_Desktop()
{
	bFreeFlyMode = false;
	FocusedObject = nullptr;
	InteractionRaycastDistance = 500.0f; // 5 meters
	InteractionUpdateRate = 0.1f; // 10 times per second
	InteractionUpdateTimer = 0.0f;
}

void APC_Desktop::BeginPlay()
{
	Super::BeginPlay();
}

void APC_Desktop::SetupInputComponent()
{
	Super::SetupInputComponent();

	// TODO: Bind input actions when using Enhanced Input system
}

void APC_Desktop::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Update interaction raycast periodically
	InteractionUpdateTimer += DeltaTime;
	if (InteractionUpdateTimer >= InteractionUpdateRate)
	{
		InteractionUpdateTimer = 0.0f;
		AActor* NewFocusedObject = PerformInteractionRaycast(InteractionRaycastDistance);

		if (NewFocusedObject != FocusedObject)
		{
			// TODO: Handle focus changed (call component events)
			FocusedObject = NewFocusedObject;
		}
	}
}

void APC_Desktop::ToggleFreeFlyMode()
{
	bFreeFlyMode = !bFreeFlyMode;

	// Apply to controlled pawn if it's a desktop pawn
	APawn_Desktop* DesktopPawn = Cast<APawn_Desktop>(GetPawn());
	if (DesktopPawn)
	{
		DesktopPawn->SetFreeFlyMode(bFreeFlyMode);
	}
}

AActor* APC_Desktop::PerformInteractionRaycast(float MaxDistance)
{
	if (!PlayerCameraManager)
	{
		return nullptr;
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * MaxDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetPawn());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		return HitResult.GetActor();
	}

	return nullptr;
}
