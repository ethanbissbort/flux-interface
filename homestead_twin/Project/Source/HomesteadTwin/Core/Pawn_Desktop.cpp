// Copyright Fluxology. All Rights Reserved.

#include "Pawn_Desktop.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"

APawn_Desktop::APawn_Desktop()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;

	// Create movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	// Initialize default values
	bFreeFlyMode = false;
	bIsSprinting = false;
	bIsSlowWalking = false;

	BaseMovementSpeed = 300.0f; // 3 m/s
	SprintMultiplier = 2.0f;
	SlowWalkMultiplier = 0.5f;
	MouseSensitivity = 1.0f;
}

void APawn_Desktop::BeginPlay()
{
	Super::BeginPlay();

	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = BaseMovementSpeed;
	}
}

void APawn_Desktop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawn_Desktop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// TODO: Bind input actions when using Enhanced Input system
}

void APawn_Desktop::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APawn_Desktop::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APawn_Desktop::MoveUp(float Value)
{
	if (bFreeFlyMode && Value != 0.0f)
	{
		AddMovementInput(FVector::UpVector, Value);
	}
}

void APawn_Desktop::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value * MouseSensitivity);
	}
}

void APawn_Desktop::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value * MouseSensitivity);
	}
}

void APawn_Desktop::StartSprint()
{
	bIsSprinting = true;
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = BaseMovementSpeed * SprintMultiplier;
	}
}

void APawn_Desktop::StopSprint()
{
	bIsSprinting = false;
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = BaseMovementSpeed;
	}
}

void APawn_Desktop::StartSlowWalk()
{
	bIsSlowWalking = true;
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = BaseMovementSpeed * SlowWalkMultiplier;
	}
}

void APawn_Desktop::StopSlowWalk()
{
	bIsSlowWalking = false;
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = BaseMovementSpeed;
	}
}

void APawn_Desktop::SetFreeFlyMode(bool bEnabled)
{
	bFreeFlyMode = bEnabled;

	// TODO: Toggle collision and gravity
}

float APawn_Desktop::GetCurrentMovementSpeed() const
{
	if (MovementComponent)
	{
		return MovementComponent->MaxSpeed;
	}
	return BaseMovementSpeed;
}
