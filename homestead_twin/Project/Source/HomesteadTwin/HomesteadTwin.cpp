// Copyright Fluxology. All Rights Reserved.

#include "HomesteadTwin.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FHomesteadTwinModule"

void FHomesteadTwinModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uproject file
}

void FHomesteadTwinModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHomesteadTwinModule, HomesteadTwin)
