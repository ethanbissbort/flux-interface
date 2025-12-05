// Copyright Fluxology. All Rights Reserved.

#include "U_TelemetryComponent.h"
#include "Components/WidgetComponent.h"

UU_TelemetryComponent::UU_TelemetryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize default values
	DisplayMode = ETelemetryDisplayMode::FloatingText;
	UpdateRate = 1.0f;
	CurrentValue = 0.0f;
	UpdateTimer = 0.0f;

	// Threshold defaults
	GreenThreshold = 80.0f;
	YellowThreshold = 60.0f;
	RedThreshold = 30.0f;
	bLowerIsBetter = false;

	// Create widget component
	FloatingTextWidget = nullptr;
}

void UU_TelemetryComponent::BeginPlay()
{
	Super::BeginPlay();

	RefreshTelemetryData();
}

void UU_TelemetryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTimer += DeltaTime;
	if (UpdateTimer >= UpdateRate)
	{
		UpdateTimer = 0.0f;
		RefreshTelemetryData();
	}
}

FString UU_TelemetryComponent::GetTelemetryValueString() const
{
	return FString::Printf(TEXT("%.2f"), CurrentValue);
}

bool UU_TelemetryComponent::IsTelemetryStale() const
{
	// Check if data is older than 2x the update rate
	FTimespan TimeSinceUpdate = FDateTime::UtcNow() - LastUpdateTimestamp;
	return TimeSinceUpdate.GetTotalSeconds() > (UpdateRate * 2.0);
}

void UU_TelemetryComponent::RefreshTelemetryData()
{
	// TODO: Fetch data from US_TelemetryManager
	// For now, just update timestamp
	LastUpdateTimestamp = FDateTime::UtcNow();

	UpdateTelemetryDisplay();
	OnTelemetryUpdated(CurrentValue);
}

void UU_TelemetryComponent::UpdateTelemetryDisplay()
{
	// TODO: Update visual display based on display mode
	FLinearColor DisplayColor = GetColorForValue(CurrentValue);

	// Apply color to widget or material based on display mode
}

FLinearColor UU_TelemetryComponent::GetColorForValue(float Value) const
{
	if (bLowerIsBetter)
	{
		if (Value <= GreenThreshold) return FLinearColor::Green;
		if (Value <= YellowThreshold) return FLinearColor::Yellow;
		return FLinearColor::Red;
	}
	else
	{
		if (Value >= GreenThreshold) return FLinearColor::Green;
		if (Value >= YellowThreshold) return FLinearColor::Yellow;
		return FLinearColor::Red;
	}
}
