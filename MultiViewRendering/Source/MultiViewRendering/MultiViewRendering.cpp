#include "MultiViewRendering.h"
#include "Engine/MultiViewRenderingSettings.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#endif
#define LOCTEXT_NAMESPACE "FMultiViewRenderingModule"

void FMultiViewRenderingModule::StartupModule()
{
#if WITH_EDITOR
	RegisterSettings();
#endif
}

void FMultiViewRenderingModule::ShutdownModule()
{
#if WITH_EDITOR
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
#endif
}

bool FMultiViewRenderingModule::SupportsDynamicReloading()
{
	return true;
}

bool FMultiViewRenderingModule::HandleSettingsSaved()
{
#if WITH_EDITOR
	UMultiViewRenderingSettings* Settings = GetMutableDefault<UMultiViewRenderingSettings>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}
#endif
	return true;
}

void FMultiViewRenderingModule::RegisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("MVR",
			LOCTEXT("RuntimeWDCategoryName", "Multi View Rendering"),
			LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the Multi View Rendering game module"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "MVR", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for our game module"),
			GetMutableDefault<UMultiViewRenderingSettings>()
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FMultiViewRenderingModule::HandleSettingsSaved);
		}
	}
#endif
}

void FMultiViewRenderingModule::UnregisterSettings()
{
#if WITH_EDITOR
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "MVR", "General");
	}
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMultiViewRenderingModule, MultiViewRendering)