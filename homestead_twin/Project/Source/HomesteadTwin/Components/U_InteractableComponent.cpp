// Copyright Fluxology. All Rights Reserved.

#include "U_InteractableComponent.h"

UU_InteractableComponent::UU_InteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize default values
	bIsFocused = false;
	bIsInteractable = true;
	InteractionPrompt = TEXT("Press E to interact");
	MaxInteractionDistance = 300.0f; // 3 meters
}

void UU_InteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UU_InteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UU_InteractableComponent::OnFocusGained()
{
	bIsFocused = true;
	OnFocusGainedEvent();
}

void UU_InteractableComponent::OnFocusLost()
{
	bIsFocused = false;
	OnFocusLostEvent();
}

void UU_InteractableComponent::OnInteract(APlayerController* PlayerController)
{
	if (!bIsInteractable)
	{
		return;
	}

	OnInteractEvent(PlayerController);
}
