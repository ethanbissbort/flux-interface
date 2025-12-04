// Copyright Fluxology. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HomesteadTwinTarget : TargetRules
{
	public HomesteadTwinTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

		ExtraModuleNames.AddRange(new string[] { "HomesteadTwin" });
	}
}
