// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BoatRace : ModuleRules
{
	public BoatRace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Water" });

		PrivateDependencyModuleNames.AddRange(new[] { "Slate", "SlateCore" });
	}
}
