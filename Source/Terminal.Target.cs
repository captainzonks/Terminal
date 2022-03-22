// © 2022, Matthew Barham. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TerminalTarget : TargetRules
{
	public TerminalTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Terminal" } );
	}
}
