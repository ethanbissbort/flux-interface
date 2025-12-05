// Copyright Fluxology. All Rights Reserved.

#include "A_Annotation.h"
#include "Components/WidgetComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"

AA_Annotation::AA_Annotation()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create root component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// Create billboard component for marker
	MarkerBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("MarkerBillboard"));
	MarkerBillboard->SetupAttachment(RootComponent);

	// Create widget component for text display
	TextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	TextWidget->SetupAttachment(RootComponent);

	// Initialize default values
	AnnotationId = FGuid();
	AnnotationText = TEXT("");
	AnnotationCategory = NAME_None;
	MarkerColor = FLinearColor::Yellow;
	TextScale = 1.0f;
}

void AA_Annotation::BeginPlay()
{
	Super::BeginPlay();

	UpdateWidgetDisplay();
}

void AA_Annotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Scale with distance for readability
}

void AA_Annotation::InitializeAnnotation(FGuid InAnnotationId, const FString& InText, FName InCategory)
{
	AnnotationId = InAnnotationId;
	AnnotationText = InText;
	AnnotationCategory = InCategory;

	UpdateWidgetDisplay();
}

void AA_Annotation::UpdateAnnotationText(const FString& NewText)
{
	AnnotationText = NewText;
	UpdateWidgetDisplay();
}

void AA_Annotation::UpdateWidgetDisplay()
{
	// TODO: Update widget to display current annotation data
	// This would typically involve updating a UMG widget with the annotation text
}
