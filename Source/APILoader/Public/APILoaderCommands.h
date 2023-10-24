// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "APILoaderStyle.h"

class FAPILoaderCommands : public TCommands<FAPILoaderCommands>
{
public:

	FAPILoaderCommands()
		: TCommands<FAPILoaderCommands>(TEXT("APILoader"), NSLOCTEXT("Contexts", "APILoader", "APILoader Plugin"), NAME_None, FAPILoaderStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};