// Copyright Fluxology. All Rights Reserved.

#include "GM_HomesteadTwin.h"

AGM_HomesteadTwin::AGM_HomesteadTwin()
{
	// Set default spawn transform
	DefaultSpawnTransform = FTransform::Identity;
	DefaultSpawnTransform.SetLocation(FVector(0.0, 0.0, 100.0)); // 1m above ground

	bForceVRMode = false;
}

void AGM_HomesteadTwin::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	OnGameModeInit();
}

void AGM_HomesteadTwin::StartPlay()
{
	Super::StartPlay();

	OnGameplayStart();
}

FTransform AGM_HomesteadTwin::GetDefaultPlayerSpawnTransform() const
{
	return DefaultSpawnTransform;
}
