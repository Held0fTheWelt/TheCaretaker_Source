// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheCaretakerEditorTarget : TargetRules
{
	public TheCaretakerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("TheCaretaker");
		ExtraModuleNames.Add("TheCaretaker_Editor");
	}
}
