// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Annotation.generated.h"

class UWidgetComponent;
class UBillboardComponent;

/**
 * AA_Annotation
 *
 * Actor representing an in-world annotation/note marker.
 *
 * Responsibilities:
 * - Visual marker at annotation position
 * - Display annotation text in 3D space
 * - Support interaction to edit/delete annotation
 * - Scale with distance for readability
 *
 * Implementation Notes:
 * - Use billboard sprite or simple mesh for marker
 * - Widget component for text display
 * - Managed by US_AnnotationManager subsystem
 * - Visibility can be toggled based on phase or category
 */
UCLASS()
class HOMESTEADTWIN_API AA_Annotation : public AActor
{
	GENERATED_BODY()

public:
	AA_Annotation();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// End AActor Interface

	/** Initialize annotation with data */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	void InitializeAnnotation(FGuid InAnnotationId, const FString& InText, FName InCategory);

	/** Update annotation text */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	void UpdateAnnotationText(const FString& NewText);

	/** Get annotation ID */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	FGuid GetAnnotationId() const { return AnnotationId; }

	/** Get annotation text */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	FString GetAnnotationText() const { return AnnotationText; }

	/** Get annotation category */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	FName GetAnnotationCategory() const { return AnnotationCategory; }

protected:
	/** Called when annotation is interacted with */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Annotation")
	void OnAnnotationInteracted();

	/** Update widget to display current annotation data */
	void UpdateWidgetDisplay();

protected:
	/** Root scene component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	USceneComponent* RootSceneComponent;

	/** Billboard sprite for marker visualization */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UBillboardComponent* MarkerBillboard;

	/** Widget component for text display */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UWidgetComponent* TextWidget;

	/** Annotation ID (matches US_AnnotationManager data) */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Data")
	FGuid AnnotationId;

	/** Annotation text content */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Data")
	FString AnnotationText;

	/** Annotation category */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Data")
	FName AnnotationCategory;

	/** Marker color based on category */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Appearance")
	FLinearColor MarkerColor;

	/** Text scale factor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Appearance")
	float TextScale;
};
