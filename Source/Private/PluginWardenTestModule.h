// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IPluginWardenTestModule.h"

static const FName PluginWardenTestTabName("PluginWardenTest");

/**
* Implements the PluginWardenTest module.
*/
class FPluginWardenTestModule : public IPluginWardenTestModule
{
public:

	//~ Begin IModuleInterface Interface

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override;

	//~ End IModuleInterface Interface

	static void ExecuteOpenPluginWardenTest()
	{
		FGlobalTabmanager::Get()->InvokeTab(PluginWardenTestTabName);
	}

private:
	// Handles creating the project settings tab.
	TSharedRef<SDockTab> HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs);
};