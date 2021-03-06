// © 2022, Matthew Barham. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TerminalEditorTarget : TargetRules
{
	public TerminalEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Terminal" } );
	}
}
