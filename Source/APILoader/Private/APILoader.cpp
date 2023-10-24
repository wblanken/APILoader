// Copyright Epic Games, Inc. All Rights Reserved.

#include "APILoader.h"
#include "APILoaderStyle.h"
#include "APILoaderCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName APILoaderTabName("APILoader");

#define LOCTEXT_NAMESPACE "FAPILoaderModule"

void FAPILoaderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAPILoaderStyle::Initialize();
	FAPILoaderStyle::ReloadTextures();

	FAPILoaderCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAPILoaderCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAPILoaderModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAPILoaderModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(APILoaderTabName, FOnSpawnTab::CreateRaw(this, &FAPILoaderModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAPILoaderTabTitle", "APILoader"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAPILoaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAPILoaderStyle::Shutdown();

	FAPILoaderCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(APILoaderTabName);
}

TSharedRef<SDockTab> FAPILoaderModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FAPILoaderModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("APILoader.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FAPILoaderModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(APILoaderTabName);
}

void FAPILoaderModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAPILoaderCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAPILoaderCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAPILoaderModule, APILoader)