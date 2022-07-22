// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ue5Gas : ModuleRules
{
	public Ue5Gas(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
