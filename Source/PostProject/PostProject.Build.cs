// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class PostProject : ModuleRules
{
	public PostProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "PhysicsCore", "GameplayTasks", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] 
		{ 
			"PostProject/Public/Player", 
			"PostProject/Public/Components", 
			"PostProject/Public/Dev",
			"PostProject/Public/Weapon",
			"PostProject/Public/UI",
			"PostProject/Public/Animations",
			"PostProject/Public/Pickups",
			"PostProject/Public/Weapon/Components",
			"PostProject/Public/AI",
			"PostProject/Public/AI/Tasks",
			"PostProject/Public/AI/Services",
			"PostProject/Public/AI/EQS",
			"PostProject/Public/AI/Decorators",
			"PostProject/Public/Sound"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
