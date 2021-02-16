// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTheCaretaker_Editor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonClicked();

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	
};
