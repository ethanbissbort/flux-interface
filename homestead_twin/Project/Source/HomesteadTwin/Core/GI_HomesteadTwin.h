// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_HomesteadTwin.generated.h"

/**
 * UGI_HomesteadTwin
 *
 * Game Instance subclass for the Homestead Twin application.
 * Persists across level loads and manages global state.
 *
 * Responsibilities:
 * - Initialize and manage subsystems (Phase Manager, SOP Manager, etc.)
 * - Maintain global application settings
 * - Handle VR/Desktop mode switching if needed
 * - Coordinate save/load operations
 *
 * Implementation Notes:
 * - This is a singleton-like object (one per application lifetime)
 * - Use subsystems for modular functionality
 * - Keep this class lightweight; delegate to subsystems
 */
UCLASS()
class HOMESTEADTWIN_API UGI_HomesteadTwin : public UGameInstance
{
	GENERATED_BODY()

public:
	UGI_HomesteadTwin();

	// Begin UGameInstance Interface
	virtual void Init() override;
	virtual void Shutdown() override;
	// End UGameInstance Interface

protected:
	/** Called when game instance is initialized */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin")
	void OnHomesteadTwinInit();

	/** Called when game instance is shutting down */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin")
	void OnHomesteadTwinShutdown();

public:
	/** Get the current application version */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin")
	FString GetApplicationVersion() const;

	/** Check if running in VR mode */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin")
	bool IsVRMode() const;

protected:
	/** Application version string */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin")
	FString ApplicationVersion;

	/** Is VR mode active */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin")
	bool bIsVRMode;
};
