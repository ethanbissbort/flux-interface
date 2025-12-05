// Copyright Fluxology. All Rights Reserved.

#include "GI_HomesteadTwin.h"

UGI_HomesteadTwin::UGI_HomesteadTwin()
{
	ApplicationVersion = TEXT("0.1.0-alpha");
	bIsVRMode = false;
}

void UGI_HomesteadTwin::Init()
{
	Super::Init();

	// TODO: Initialize subsystems

	OnHomesteadTwinInit();
}

void UGI_HomesteadTwin::Shutdown()
{
	OnHomesteadTwinShutdown();

	Super::Shutdown();
}

FString UGI_HomesteadTwin::GetApplicationVersion() const
{
	return ApplicationVersion;
}

bool UGI_HomesteadTwin::IsVRMode() const
{
	return bIsVRMode;
}
