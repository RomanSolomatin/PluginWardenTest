// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PluginWardenTestPrivatePCH.h"
#include "PluginWardenTestModule.h"

#include "IPluginWardenModule.h"

#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"
#include "SDockTab.h"
#include "SThrobber.h"
#include "SEditableTextBox.h"

#define LOCTEXT_NAMESPACE "PluginWardenTest"

void FPluginWardenTestModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PluginWardenTestTabName, FOnSpawnTab::CreateRaw(this, &FPluginWardenTestModule::HandleSpawnSettingsTab))
		.SetDisplayName(LOCTEXT("PluginWardenTestTabTitle", "Plugin Warden Test"))
		.SetTooltipText(LOCTEXT("PluginWardenTestTooltipText", "Open the Plugin Warden Test tab."))
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "PluginWardenTest.TabIcon"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory());
}

void FPluginWardenTestModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PluginWardenTestTabName);
}

bool FPluginWardenTestModule::SupportsDynamicReloading()
{
	return true;
}

TSharedRef<SDockTab> FPluginWardenTestModule::HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs)
{
	const TSharedRef<SDockTab> DockTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab);

	DockTab->SetContent(
		SNew(SOverlay)

		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(LOCTEXT("NoAuthMsg", "Please buy our plug-in on the Marketplace :)"))
		]
	);

	IPluginWardenModule::Get().CheckEntitlementForPlugin(
		LOCTEXT("PluginWardenTest", "Plugin Warden Test"),
		TEXT("GET_ITEM_ID_FROM_MARKETPLACE_STAFF"),
		TEXT("GET_OFFER_ID_FROM_MARKETPLACE_STAFF"),
		[&] () {
			DockTab->SetContent(
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock).Text(LOCTEXT("AuthMsg", "Behold!  Authorized Plugin Goodness!"))
			]
		);
	});

	return DockTab;
}


IMPLEMENT_MODULE(FPluginWardenTestModule, PluginWardenTest);


#undef LOCTEXT_NAMESPACE
