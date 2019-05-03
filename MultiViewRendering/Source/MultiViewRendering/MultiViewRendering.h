#pragma once

#include "CoreMinimal.h"
#include "Engine/MultiViewLocalPlayer.h"
#include "Engine/MultiViewGameViewportClient.h"
#include "Modules/ModuleManager.h"

class FMultiViewRenderingModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
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
};