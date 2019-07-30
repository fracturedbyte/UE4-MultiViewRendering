#include "MultiViewRendering.h"
#include "Engine/MultiViewRenderingSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FMultiViewRenderingModule"

void FMultiViewRenderingModule::StartupModule()
{
	RegisterSettings();
}

void FMultiViewRenderingModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

bool FMultiViewRenderingModule::SupportsDynamicReloading()
{
	return true;
}

bool FMultiViewRenderingModule::HandleSettingsSaved()
{
	UMultiViewRenderingSettings* Settings = GetMutableDefault<UMultiViewRenderingSettings>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FMultiViewRenderingModule::RegisterSettings()
{
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
}

void FMultiViewRenderingModule::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "MVR", "General");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMultiViewRenderingModule, MultiViewRendering)