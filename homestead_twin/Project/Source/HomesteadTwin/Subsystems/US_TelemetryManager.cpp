// Copyright Fluxology. All Rights Reserved.

#include "US_TelemetryManager.h"
#include "TimerManager.h"

UUS_TelemetryManager::UUS_TelemetryManager()
{
	bTelemetryActive = false;
	bMockDataMode = true; // Default to mock mode for testing
}

void UUS_TelemetryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUS_TelemetryManager::Deinitialize()
{
	StopTelemetry();

	Super::Deinitialize();
}

void UUS_TelemetryManager::StartTelemetry()
{
	if (bTelemetryActive)
	{
		return;
	}

	bTelemetryActive = true;

	// Start polling timer if not in mock mode
	if (!bMockDataMode && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TelemetryPollTimerHandle,
			this,
			&UUS_TelemetryManager::PollTelemetryEndpoints,
			5.0f, // Poll every 5 seconds
			true
		);
	}
	else if (bMockDataMode)
	{
		// Generate initial mock data
		GenerateMockData();
	}
}

void UUS_TelemetryManager::StopTelemetry()
{
	if (!bTelemetryActive)
	{
		return;
	}

	bTelemetryActive = false;

	// Clear polling timer
	if (GetWorld() && TelemetryPollTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TelemetryPollTimerHandle);
	}
}

float UUS_TelemetryManager::GetTelemetryValue(FName Key, bool& bSuccess) const
{
	const float* Value = TelemetryDataCache.Find(Key);
	bSuccess = (Value != nullptr);
	return bSuccess ? *Value : 0.0f;
}

FString UUS_TelemetryManager::GetTelemetryString(FName Key, bool& bSuccess) const
{
	float Value = GetTelemetryValue(Key, bSuccess);
	return bSuccess ? FString::Printf(TEXT("%.2f"), Value) : TEXT("N/A");
}

FDateTime UUS_TelemetryManager::GetTelemetryTimestamp(FName Key) const
{
	const FDateTime* Timestamp = TelemetryTimestamps.Find(Key);
	return Timestamp ? *Timestamp : FDateTime::MinValue();
}

void UUS_TelemetryManager::SetMockDataMode(bool bEnabled)
{
	bMockDataMode = bEnabled;

	if (bTelemetryActive)
	{
		// Restart telemetry with new mode
		StopTelemetry();
		StartTelemetry();
	}
}

void UUS_TelemetryManager::PollTelemetryEndpoints()
{
	// TODO: Implement HTTP requests to configured endpoints
	// For now, just use mock data
	if (bMockDataMode)
	{
		GenerateMockData();
	}
}

void UUS_TelemetryManager::GenerateMockData()
{
	// Generate randomized mock telemetry data for testing
	TArray<FName> MockKeys = {
		FName("PowerUsage"),
		FName("BatteryCharge"),
		FName("SolarProduction"),
		FName("Temperature"),
		FName("Humidity")
	};

	FDateTime Now = FDateTime::UtcNow();

	for (const FName& Key : MockKeys)
	{
		// Generate random values
		float Value = FMath::FRandRange(0.0f, 100.0f);

		TelemetryDataCache.Add(Key, Value);
		TelemetryTimestamps.Add(Key, Now);

		OnTelemetryDataUpdated(Key, Value);
	}
}
