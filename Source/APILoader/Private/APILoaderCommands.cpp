// Copyright Epic Games, Inc. All Rights Reserved.

#include "APILoaderCommands.h"

#define LOCTEXT_NAMESPACE "FAPILoaderModule"

void FAPILoaderCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "APILoader", "Bring up APILoader window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
