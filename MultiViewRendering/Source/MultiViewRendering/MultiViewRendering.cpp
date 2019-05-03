#include "MultiViewRendering.h"
#include "Engine/MultiViewRenderingDevice.h"

#define LOCTEXT_NAMESPACE "FMultiViewRenderingModule"

void FMultiViewRenderingModule::StartupModule()
{}

void FMultiViewRenderingModule::ShutdownModule()
{}

bool FMultiViewRenderingModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMultiViewRenderingModule, MultiViewRendering)