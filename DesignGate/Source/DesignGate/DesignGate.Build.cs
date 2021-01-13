// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DesignGate : ModuleRules
{
	public DesignGate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
