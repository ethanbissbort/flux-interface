// Copyright Fluxology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * FHomesteadTwinModule
 *
 * Main module for the Homestead Twin application.
 */
class FHomesteadTwinModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
