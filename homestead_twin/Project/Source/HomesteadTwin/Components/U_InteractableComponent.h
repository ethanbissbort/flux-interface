// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "U_InteractableComponent.generated.h"

/**
 * UU_InteractableComponent
 *
 * Component that makes an actor interactable by player.
 *
 * Responsibilities:
 * - Detect when player is looking at this object
 * - Handle interaction input (E key / VR trigger)
 * - Show interaction prompt/reticle
 * - Trigger interaction events for UI to display object info
 *
 * Implementation Notes:
 * - Attach to AA_HomesteadObject or any actor
 * - PlayerController performs raycast and checks for this component
 * - Events can be handled in Blueprint or C++
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOMESTEADTWIN_API UU_InteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UU_InteractableComponent();

	// Begin UActorComponent Interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// End UActorComponent Interface

	/** Called when player starts looking at this object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Interaction")
	void OnFocusGained();

	/** Called when player stops looking at this object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Interaction")
	void OnFocusLost();

	/** Called when player interacts with this object */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Interaction")
	void OnInteract(APlayerController* PlayerController);

	/** Check if object is currently focused */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Interaction")
	bool IsFocused() const { return bIsFocused; }

	/** Check if object is interactable (can be disabled) */
	UFUNCTION(BlueprintPure, Category = "Homestead Twin|Interaction")
	bool IsInteractable() const { return bIsInteractable; }

	/** Enable/disable interaction */
	UFUNCTION(BlueprintCallable, Category = "Homestead Twin|Interaction")
	void SetInteractable(bool bEnabled) { bIsInteractable = bEnabled; }

protected:
	/** Blueprint event: focus gained */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Interaction")
	void OnFocusGainedEvent();

	/** Blueprint event: focus lost */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Interaction")
	void OnFocusLostEvent();

	/** Blueprint event: interacted */
	UFUNCTION(BlueprintImplementableEvent, Category = "Homestead Twin|Interaction")
	void OnInteractEvent(APlayerController* PlayerController);

protected:
	/** Is this object currently focused by player */
	UPROPERTY(BlueprintReadOnly, Category = "Homestead Twin|Interaction")
	bool bIsFocused;

	/** Is interaction enabled for this object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Interaction")
	bool bIsInteractable;

	/** Interaction prompt text (e.g., "Press E to examine") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Interaction")
	FString InteractionPrompt;

	/** Maximum interaction distance (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homestead Twin|Interaction")
	float MaxInteractionDistance;
};
