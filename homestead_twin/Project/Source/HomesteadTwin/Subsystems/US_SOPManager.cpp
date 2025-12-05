// Copyright Fluxology. All Rights Reserved.

#include "US_SOPManager.h"
#include "Misc/Paths.h"

UUS_SOPManager::UUS_SOPManager()
{
}

void UUS_SOPManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUS_SOPManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUS_SOPManager::LoadSOPData()
{
	// TODO: Load SOP data from JSON files
}

FStandardOperatingProcedure UUS_SOPManager::GetSOPById(FName SOPId) const
{
	// TODO: Implement lookup
	return FStandardOperatingProcedure();
}

TArray<FStandardOperatingProcedure> UUS_SOPManager::GetSOPsForObject(FName ObjectId) const
{
	// TODO: Implement lookup
	return TArray<FStandardOperatingProcedure>();
}

TArray<FStandardOperatingProcedure> UUS_SOPManager::GetAllSOPs() const
{
	// TODO: Implement
	return TArray<FStandardOperatingProcedure>();
}

TArray<FName> UUS_SOPManager::SearchSOPs(const FString& SearchQuery) const
{
	// TODO: Implement search
	return TArray<FName>();
}
