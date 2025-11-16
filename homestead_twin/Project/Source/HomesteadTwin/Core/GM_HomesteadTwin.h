// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_HomesteadTwin.generated.h"

/**
 * AGM_HomesteadTwin
 *
 * Game Mode for the Homestead Twin application.
 * Defines the rules and configuration for the main homestead map.
 *
 * Responsibilities:
 * - Specify default pawn classes (desktop vs VR)
 * - Specify player controller classes
 * - Handle player spawn logic
 * - Manage level-specific game state
 *
 * Implementation Notes:
 * - Single-player only (no multiplayer support)
 * - May have separate game modes for different maps if needed
 * - Keep lightweight; most logic should be in subsystems or actors
 */
UCLASS()
class HOMESTEADTWIN_API AGM_HomesteadTwin : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_HomesteadTwin();

	// Begin AGameModeBase Interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	// End AGameModeBase Interface

protected:
	/** Called when game mode is initialized */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin")
	void OnGameModeInit();

	/** Called when gameplay starts */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin")
	void OnGameplayStart();

public:
	/** Get the default spawn transform for the player */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin")
	FTransform GetDefaultPlayerSpawnTransform() const;

protected:
	/** Default spawn location (relative to world origin) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Spawn")
	FTransform DefaultSpawnTransform;

	/** Whether to force VR mode for this map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|VR")
	bool bForceVRMode;
};
