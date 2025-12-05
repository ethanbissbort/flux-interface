// Copyright Fluxology. All Rights Reserved.

#include "US_AnnotationManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"

UUS_AnnotationManager::UUS_AnnotationManager()
{
	SaveFilePath = FPaths::ProjectSavedDir() / TEXT("Annotations/annotations.json");
}

void UUS_AnnotationManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Load annotations from file if exists
	LoadAnnotations();
}

void UUS_AnnotationManager::Deinitialize()
{
	// Save annotations before shutdown
	SaveAnnotations();

	Super::Deinitialize();
}

FGuid UUS_AnnotationManager::CreateAnnotation(FVector WorldPosition, const FString& Text, FName Category)
{
	FAnnotation NewAnnotation;
	NewAnnotation.AnnotationId = FGuid::NewGuid();
	NewAnnotation.WorldPosition = WorldPosition;
	NewAnnotation.Text = Text;
	NewAnnotation.Category = Category;
	NewAnnotation.CreatedTimestamp = FDateTime::Now();
	NewAnnotation.ModifiedTimestamp = FDateTime::Now();

	AnnotationDatabase.Add(NewAnnotation.AnnotationId, NewAnnotation);

	OnAnnotationCreated(NewAnnotation);

	return NewAnnotation.AnnotationId;
}

bool UUS_AnnotationManager::UpdateAnnotation(FGuid AnnotationId, const FString& NewText, FName NewCategory)
{
	FAnnotation* Annotation = AnnotationDatabase.Find(AnnotationId);
	if (!Annotation)
	{
		return false;
	}

	Annotation->Text = NewText;
	if (NewCategory != NAME_None)
	{
		Annotation->Category = NewCategory;
	}
	Annotation->ModifiedTimestamp = FDateTime::Now();

	OnAnnotationUpdated(*Annotation);

	return true;
}

bool UUS_AnnotationManager::DeleteAnnotation(FGuid AnnotationId)
{
	if (AnnotationDatabase.Remove(AnnotationId) > 0)
	{
		OnAnnotationDeleted(AnnotationId);
		return true;
	}
	return false;
}

FAnnotation UUS_AnnotationManager::GetAnnotation(FGuid AnnotationId) const
{
	const FAnnotation* Annotation = AnnotationDatabase.Find(AnnotationId);
	return Annotation ? *Annotation : FAnnotation();
}

TArray<FAnnotation> UUS_AnnotationManager::GetAllAnnotations() const
{
	TArray<FAnnotation> Annotations;
	AnnotationDatabase.GenerateValueArray(Annotations);
	return Annotations;
}

TArray<FAnnotation> UUS_AnnotationManager::GetAnnotationsByCategory(FName Category) const
{
	TArray<FAnnotation> FilteredAnnotations;
	for (const auto& Pair : AnnotationDatabase)
	{
		if (Pair.Value.Category == Category)
		{
			FilteredAnnotations.Add(Pair.Value);
		}
	}
	return FilteredAnnotations;
}

TArray<FAnnotation> UUS_AnnotationManager::GetAnnotationsByPhase(int32 Phase) const
{
	TArray<FAnnotation> FilteredAnnotations;
	for (const auto& Pair : AnnotationDatabase)
	{
		if (Pair.Value.AssociatedPhase == Phase)
		{
			FilteredAnnotations.Add(Pair.Value);
		}
	}
	return FilteredAnnotations;
}

TArray<FAnnotation> UUS_AnnotationManager::GetAnnotationsNearPosition(FVector WorldPosition, float Radius) const
{
	TArray<FAnnotation> NearbyAnnotations;
	float RadiusSquared = Radius * Radius;

	for (const auto& Pair : AnnotationDatabase)
	{
		float DistanceSquared = FVector::DistSquared(WorldPosition, Pair.Value.WorldPosition);
		if (DistanceSquared <= RadiusSquared)
		{
			NearbyAnnotations.Add(Pair.Value);
		}
	}

	return NearbyAnnotations;
}

bool UUS_AnnotationManager::SaveAnnotations()
{
	// TODO: Implement JSON serialization
	return true;
}

bool UUS_AnnotationManager::LoadAnnotations()
{
	// TODO: Implement JSON deserialization
	return true;
}
