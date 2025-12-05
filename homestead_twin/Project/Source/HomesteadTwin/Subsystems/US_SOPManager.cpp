// Copyright Fluxology. All Rights Reserved.

#include "US_SOPManager.h"
#include "Misc/Paths.h"

UUS_SOPManager::UUS_SOPManager()
{
}

void UUS_SOPManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadSOPData();
}

void UUS_SOPManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUS_SOPManager::LoadSOPData()
{
	// TODO: Load SOP data from data table
	// If SOPDataTable is set, iterate through it and populate SOPDatabase
}

FStandardOperatingProcedure UUS_SOPManager::GetSOPById(FName SOPId) const
{
	const FStandardOperatingProcedure* SOP = SOPDatabase.Find(SOPId);
	return SOP ? *SOP : FStandardOperatingProcedure();
}

TArray<FStandardOperatingProcedure> UUS_SOPManager::GetSOPsForObject(FName ObjectId) const
{
	TArray<FStandardOperatingProcedure> SOPs;
	for (const auto& Pair : SOPDatabase)
	{
		if (Pair.Value.LinkedObjectIds.Contains(ObjectId))
		{
			SOPs.Add(Pair.Value);
		}
	}
	return SOPs;
}

TArray<FStandardOperatingProcedure> UUS_SOPManager::GetSOPsByTag(FName Tag) const
{
	TArray<FStandardOperatingProcedure> SOPs;
	for (const auto& Pair : SOPDatabase)
	{
		if (Pair.Value.Tags.Contains(Tag))
		{
			SOPs.Add(Pair.Value);
		}
	}
	return SOPs;
}

TArray<FStandardOperatingProcedure> UUS_SOPManager::GetAllSOPs() const
{
	TArray<FStandardOperatingProcedure> SOPs;
	SOPDatabase.GenerateValueArray(SOPs);
	return SOPs;
}

TArray<FStandardOperatingProcedure> UUS_SOPManager::SearchSOPs(const FString& SearchText) const
{
	TArray<FStandardOperatingProcedure> Results;
	FString LowerSearchText = SearchText.ToLower();

	for (const auto& Pair : SOPDatabase)
	{
		if (Pair.Value.Title.ToLower().Contains(LowerSearchText) ||
			Pair.Value.Description.ToLower().Contains(LowerSearchText))
		{
			Results.Add(Pair.Value);
		}
	}

	return Results;
}
