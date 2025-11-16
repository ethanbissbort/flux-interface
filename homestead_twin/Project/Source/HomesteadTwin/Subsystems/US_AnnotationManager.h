// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "US_AnnotationManager.generated.h"

/**
 * FAnnotation
 *
 * Data structure for an in-world annotation/note.
 */
USTRUCT(BlueprintType)
struct FAnnotation
{
	GENERATED_BODY()

	/** Unique annotation ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FGuid AnnotationId;

	/** World position of annotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FVector WorldPosition;

	/** Annotation text content */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FString Text;

	/** Category/tag for organization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FName Category;

	/** Timestamp of creation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FDateTime CreatedTimestamp;

	/** Timestamp of last edit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FDateTime ModifiedTimestamp;

	/** Optional phase association */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	int32 AssociatedPhase;

	/** Optional linked object ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Annotation")
	FName LinkedObjectId;

	FAnnotation()
		: AnnotationId(FGuid::NewGuid())
		, WorldPosition(FVector::ZeroVector)
		, Text(TEXT(""))
		, Category(NAME_None)
		, CreatedTimestamp(FDateTime::Now())
		, ModifiedTimestamp(FDateTime::Now())
		, AssociatedPhase(-1)
		, LinkedObjectId(NAME_None)
	{}
};

/**
 * UUS_AnnotationManager
 *
 * Game Instance Subsystem for managing in-world annotations.
 *
 * Responsibilities:
 * - Create, read, update, delete annotations
 * - Persist annotations to JSON file
 * - Spawn/despawn annotation actors in world
 * - Query annotations by category, phase, or proximity
 *
 * Implementation Notes:
 * - Annotations saved to local JSON file (in Saved/Annotations/)
 * - Annotation actors spawned dynamically based on visibility rules
 * - Support filtering by phase (hide annotations for future phases)
 */
UCLASS()
class HOMESTEADTWIN_API UUS_AnnotationManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUS_AnnotationManager();

	// Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface

	/** Create a new annotation */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	FGuid CreateAnnotation(FVector WorldPosition, const FString& Text, FName Category = NAME_None);

	/** Update an existing annotation */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	bool UpdateAnnotation(FGuid AnnotationId, const FString& NewText, FName NewCategory = NAME_None);

	/** Delete an annotation */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	bool DeleteAnnotation(FGuid AnnotationId);

	/** Get annotation by ID */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	FAnnotation GetAnnotation(FGuid AnnotationId) const;

	/** Get all annotations */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	TArray<FAnnotation> GetAllAnnotations() const;

	/** Get annotations by category */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	TArray<FAnnotation> GetAnnotationsByCategory(FName Category) const;

	/** Get annotations by phase */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Annotation")
	TArray<FAnnotation> GetAnnotationsByPhase(int32 Phase) const;

	/** Get annotations near a world position */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	TArray<FAnnotation> GetAnnotationsNearPosition(FVector WorldPosition, float Radius = 1000.0f) const;

	/** Save annotations to JSON file */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	bool SaveAnnotations();

	/** Load annotations from JSON file */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Annotation")
	bool LoadAnnotations();

protected:
	/** Called when an annotation is created */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Annotation")
	void OnAnnotationCreated(const FAnnotation& Annotation);

	/** Called when an annotation is updated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Annotation")
	void OnAnnotationUpdated(const FAnnotation& Annotation);

	/** Called when an annotation is deleted */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Annotation")
	void OnAnnotationDeleted(FGuid AnnotationId);

protected:
	/** Annotation data storage */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Annotation")
	TMap<FGuid, FAnnotation> AnnotationDatabase;

	/** Path to JSON save file */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Annotation")
	FString SaveFilePath;
};
