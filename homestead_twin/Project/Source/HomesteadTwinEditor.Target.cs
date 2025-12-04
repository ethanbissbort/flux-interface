// Copyright Fluxology. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HomesteadTwinEditorTarget : TargetRules
{
	public HomesteadTwinEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

		ExtraModuleNames.AddRange(new string[] { "HomesteadTwin" });
	}
}
