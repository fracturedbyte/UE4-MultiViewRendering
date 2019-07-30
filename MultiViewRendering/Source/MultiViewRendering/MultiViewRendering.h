#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMultiViewRenderingModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
	bool SupportsDynamicReloading() override;

	static inline FMultiViewRenderingModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FMultiViewRenderingModule>("MultiViewRendering");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("MultiViewRendering");
	}

private:

	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();
};