// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheCaretaker : ModuleRules
{
	public TheCaretaker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"HeadMountedDisplay", 
				"AIModule", 
				"GameplayTasks", 
				"Slate", 
				"SlateCore",
				"UMG", 
			});

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"FMODStudio",
			});
			
	}
}
