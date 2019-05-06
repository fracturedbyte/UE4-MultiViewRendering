#include "MultiViewFunctionLibrary.h"

UMultiViewFunctionLibrary::UMultiViewFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

bool UMultiViewFunctionLibrary::SetupTripleScreenWindow()
{
	if (!IsTripleScreenSetup())
		return false;

	if (GEngine && GEngine->GameViewport)
	{
		if (auto Window = GEngine->GameViewport->GetWindow())
		{
			FPlatformRect VirtualSize = GetVirtualDisplayRect();
			FVector2D Offset(VirtualSize.Left, VirtualSize.Top);
			FVector2D Size(VirtualSize.Right - VirtualSize.Left, VirtualSize.Bottom - VirtualSize.Top);

			Window->ReshapeWindow(Offset, Size);
			return true;
		}
	}

	return false;
}

bool UMultiViewFunctionLibrary::IsTripleScreenSetup()
{
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	return DisplayMetrics.MonitorInfo.Num() == 3;
}

bool UMultiViewFunctionLibrary::EnableTripleScreenRendering(bool bEnable)
{
	if (GEngine && GEngine->StereoRenderingDevice.IsValid())
	{
		return GEngine->StereoRenderingDevice->EnableStereo(bEnable);
	}

	return false;
}

FPlatformRect UMultiViewFunctionLibrary::GetVirtualDisplayRect()
{
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	return DisplayMetrics.VirtualDisplayRect;
}