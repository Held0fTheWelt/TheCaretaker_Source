// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCaretaker_Editor.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Interfaces/IMainFrameModule.h"
#include "EditorUtilityWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"

static const FName CaretakerTabName("Caretaker");

#define LOCTEXT_NAMESPACE "FTheCaretaker_Editor"

void FTheCaretaker_Editor::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	/*FCaretakerStyle::Initialize();
	FCaretakerStyle::ReloadTextures();

	FCaretakerCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCaretakerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTheCaretaker_Editor::PluginButtonClicked),
		FCanExecuteAction());

	IMainFrameModule& mainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	mainFrame.GetMainFrameCommandBindings()->Append(PluginCommands.ToSharedRef());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("FileProject", EExtensionHook::First, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FTheCaretaker_Editor::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FTheCaretaker_Editor::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}*/
}

void FTheCaretaker_Editor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
// we call this function before unloading the module.
	//FCaretakerStyle::Shutdown();

	//FCaretakerCommands::Unregister();
}

void FTheCaretaker_Editor::PluginButtonClicked()
{
	//FUnrealEdMisc::Get().RestartEditor(false);

	//struct FConstructorStatics
	//{		
	//	ConstructorHelpers::FClassFinder<UEditorUtilityWidget> Editor;
	//	FConstructorStatics()
	//		: Editor(TEXT("/Game/Editor/UtilityWidget/GameSetup.GameSetup"))
	//	{
	//	}
	//};		

	//static FConstructorStatics ConstructorStatics;
	//
	//UEditorUtilityWidget* EditorUtility = ConstructorStatics.Editor.Class.GetDefaultObject();
	//
	//if (EditorUtility == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Editor Utility Widget was null"));
	//}
	//else
	//{
	//	EditorUtility->ExecuteDefaultAction();
	//}
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTheCaretaker_Editor, TheCaretaker_Editor);