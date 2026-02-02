// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SmartEnemyAI : ModuleRules
{
	public SmartEnemyAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SmartEnemyAI",
            "SmartEnemyAI/Variant/Variant_Platforming",
            "SmartEnemyAI/Variant/Variant_Combat",
            "SmartEnemyAI/Variant/Variant_Combat/AI",
            "SmartEnemyAI/Variant/Variant_SideScrolling",
            "SmartEnemyAI/Variant/Variant_SideScrolling/Gameplay",
            "SmartEnemyAI/Variant/Variant_SideScrolling/AI"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
