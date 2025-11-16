// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "U_TelemetryComponent.generated.h"

class UWidgetComponent;

/**
 * ETelemetryDisplayMode
 *
 * How telemetry data should be displayed.
 */
UENUM(BlueprintType)
enum class ETelemetryDisplayMode : uint8
{
	FloatingText    UMETA(DisplayName = "Floating Text"),
	ColorOverlay    UMETA(DisplayName = "Color Overlay"),
	Graph           UMETA(DisplayName = "Graph (when focused)"),
	None            UMETA(DisplayName = "No Display")
};

/**
 * UU_TelemetryComponent
 *
 * Component that displays live telemetry data on an actor. (FUTURE PHASE F)
 *
 * Responsibilities:
 * - Fetch telemetry data from US_TelemetryManager
 * - Display data visually (text, color, graph)
 * - Update at configurable intervals
 * - Support multiple telemetry keys per object
 *
 * Implementation Notes:
 * - Attach to AA_HomesteadObject (e.g., rack, PV array, battery)
 * - Data fetched from US_TelemetryManager by key
 * - Display mode can be text overlay, color change, or graph widget
 * - Gracefully handle missing/stale data (offline mode)
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOMESTEADTWIN_API UU_TelemetryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UU_TelemetryComponent();

	// Begin UActorComponent Interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// End UActorComponent Interface

	/** Get current telemetry value for primary key */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	float GetTelemetryValue() const { return CurrentValue; }

	/** Get current telemetry value as string */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	FString GetTelemetryValueString() const;

	/** Get timestamp of last telemetry update */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	FDateTime GetLastUpdateTimestamp() const { return LastUpdateTimestamp; }

	/** Check if telemetry data is stale (no update recently) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Telemetry")
	bool IsTelemetryStale() const;

	/** Manually refresh telemetry data */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Telemetry")
	void RefreshTelemetryData();

protected:
	/** Called when telemetry data is updated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Telemetry")
	void OnTelemetryUpdated(float NewValue);

	/** Update telemetry display based on current value */
	void UpdateTelemetryDisplay();

	/** Get color based on value and thresholds */
	FLinearColor GetColorForValue(float Value) const;

protected:
	/** Primary telemetry key to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Telemetry")
	FName TelemetryKey;

	/** Additional telemetry keys (for multi-value display) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Telemetry")
	TArray<FName> AdditionalTelemetryKeys;

	/** Display mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Telemetry")
	ETelemetryDisplayMode DisplayMode;

	/** Update rate (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Telemetry")
	float UpdateRate;

	/** Current telemetry value */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Telemetry")
	float CurrentValue;

	/** Timestamp of last update */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Telemetry")
	FDateTime LastUpdateTimestamp;

	/** Widget component for floating text display */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homestead Twin|Components")
	UWidgetComponent* FloatingTextWidget;

	/** Threshold for green color (normal) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Thresholds")
	float GreenThreshold;

	/** Threshold for yellow color (warning) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Thresholds")
	float YellowThreshold;

	/** Threshold for red color (critical) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Thresholds")
	float RedThreshold;

	/** Is lower value better (true) or higher value better (false) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Thresholds")
	bool bLowerIsBetter;

private:
	/** Timer for update rate */
	float UpdateTimer;
};
