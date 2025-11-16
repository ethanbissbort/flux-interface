// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "US_TelemetryManager.generated.h"

/**
 * ETelemetrySourceType
 *
 * Type of telemetry data source.
 */
UENUM(BlueprintType)
enum class ETelemetrySourceType : uint8
{
	REST_API    UMETA(DisplayName = "REST API"),
	MQTT        UMETA(DisplayName = "MQTT Topic"),
	Database    UMETA(DisplayName = "Database Query"),
	Mock        UMETA(DisplayName = "Mock/Dummy Data")
};

/**
 * FTelemetryEndpoint
 *
 * Configuration for a telemetry data source.
 */
USTRUCT(BlueprintType)
struct FTelemetryEndpoint
{
	GENERATED_BODY()

	/** Unique identifier for this endpoint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	FName EndpointId;

	/** Source type (REST, MQTT, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	ETelemetrySourceType SourceType;

	/** URL or connection string */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	FString EndpointURL;

	/** Poll interval in seconds (0 = event-driven) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	float PollInterval;

	/** Is this endpoint currently enabled */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	bool bEnabled;

	FTelemetryEndpoint()
		: EndpointId(NAME_None)
		, SourceType(ETelemetrySourceType::Mock)
		, EndpointURL(TEXT(""))
		, PollInterval(5.0f)
		, bEnabled(true)
	{}
};

/**
 * UUS_TelemetryManager
 *
 * Game Instance Subsystem for managing live telemetry data. (FUTURE PHASE F)
 *
 * Responsibilities:
 * - Poll REST endpoints or subscribe to MQTT topics
 * - Cache telemetry data with timestamps
 * - Provide data to telemetry components
 * - Support mock/dummy data mode for testing
 * - Handle connection failures gracefully (offline mode)
 *
 * Implementation Notes:
 * - Uses async HTTP requests or MQTT client library
 * - Data cached in memory with configurable retention
 * - Mock mode generates randomized test data
 * - Designed for air-gap operation (no hard dependency on endpoints)
 */
UCLASS()
class HOMESTEADTWIN_API UUS_TelemetryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUS_TelemetryManager();

	// Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface

	/** Start telemetry polling */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Telemetry")
	void StartTelemetry();

	/** Stop telemetry polling */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Telemetry")
	void StopTelemetry();

	/** Get telemetry value by key */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	float GetTelemetryValue(FName Key, bool& bSuccess) const;

	/** Get telemetry value as string */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	FString GetTelemetryString(FName Key, bool& bSuccess) const;

	/** Get timestamp of last update for a key */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	FDateTime GetTelemetryTimestamp(FName Key) const;

	/** Check if telemetry system is running */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	bool IsTelemetryActive() const { return bTelemetryActive; }

	/** Enable/disable mock data mode */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Telemetry")
	void SetMockDataMode(bool bEnabled);

	/** Check if in mock data mode */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	bool IsMockDataMode() const { return bMockDataMode; }

protected:
	/** Called when telemetry data is updated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Telemetry")
	void OnTelemetryDataUpdated(FName Key, float Value);

	/** Poll telemetry endpoints (called on timer) */
	void PollTelemetryEndpoints();

	/** Generate mock telemetry data */
	void GenerateMockData();

protected:
	/** Telemetry data cache (key -> value) */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Telemetry")
	TMap<FName, float> TelemetryDataCache;

	/** Telemetry timestamp cache (key -> timestamp) */
	UPROPERTY()
	TMap<FName, FDateTime> TelemetryTimestamps;

	/** Configured telemetry endpoints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Telemetry")
	TArray<FTelemetryEndpoint> TelemetryEndpoints;

	/** Is telemetry system active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Telemetry")
	bool bTelemetryActive;

	/** Is mock data mode enabled */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Telemetry")
	bool bMockDataMode;

	/** Telemetry polling timer handle */
	FTimerHandle TelemetryPollTimerHandle;
};
