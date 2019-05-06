using UnrealBuildTool;

public class MultiViewRendering : ModuleRules
{
	public MultiViewRendering(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"RHI",
				"SlateCore",
				"ApplicationCore",
			}
			);
	}
}