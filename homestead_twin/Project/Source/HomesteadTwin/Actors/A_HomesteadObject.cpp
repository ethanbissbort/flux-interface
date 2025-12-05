// Copyright Fluxology. All Rights Reserved.

#include "A_HomesteadObject.h"
#include "Components/StaticMeshComponent.h"

AA_HomesteadObject::AA_HomesteadObject()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create default visual mesh component
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	RootComponent = VisualMesh;

	// Initialize component pointers to nullptr
	// These will be created and attached as needed
	InteractableComponent = nullptr;
	SOPComponent = nullptr;
	TelemetryComponent = nullptr;

	// Set default metadata
	ObjectId = NAME_None;
	Category = NAME_None;
	Description = TEXT("");
}

void AA_HomesteadObject::BeginPlay()
{
	Super::BeginPlay();

	// Call blueprint event
	OnHomesteadObjectInit();
}

void AA_HomesteadObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
