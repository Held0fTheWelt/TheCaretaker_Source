// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class TheCaretaker_Editor : ModuleRules
{
	public TheCaretaker_Editor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrecompileForTargets = PrecompileTargetsType.Any;
		
		PublicIncludePaths.AddRange(
			new string[] 
			{
                Path.Combine(ModuleDirectory, "Public")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
				
			}
			);

		bEnforceIWYU = true;
		//
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",

			}///
	   );//
		  //
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"TheCaretaker",
				"Blutility",
				"UMG",
				"UMGEditor",
				"AssetTools",
				"EditorStyle"
			}///
		);//


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
			}
			);

	}
}
