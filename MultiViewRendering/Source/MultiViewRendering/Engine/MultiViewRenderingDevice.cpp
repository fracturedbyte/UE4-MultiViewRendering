#include "MultiViewRenderingDevice.h"
#include "MultiViewRenderingSettings.h"

FMultiViewRenderingDevice::FMultiViewRenderingDevice()
{
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	nScreen = DisplayMetrics.MonitorInfo.Num();
	if (nScreen == 3)
	{
		const auto& MonitorInfo = DisplayMetrics.MonitorInfo[0];
		Aspect = MonitorInfo.NativeWidth / (float)MonitorInfo.NativeHeight;

		// Monitors MUST have same resolution and same physical size to achieve correct projection
		bool bSameResolution = true;
		for (const auto& mi : DisplayMetrics.MonitorInfo)
		{
			if (mi.NativeWidth != MonitorInfo.NativeWidth ||
				mi.NativeHeight != MonitorInfo.NativeHeight)
			{
				bSameResolution = false;
				break;
			}
		}

		bStereoPossible = bSameResolution;
	}
}

FMultiViewRenderingDevice::~FMultiViewRenderingDevice()
{}

bool FMultiViewRenderingDevice::IsStereoEnabled() const
{
	return bStereoPossible && bStereoEnabled;
}

bool FMultiViewRenderingDevice::EnableStereo(bool stereo)
{
	bStereoEnabled = stereo;
	return IsStereoEnabled();
}

EStereoscopicPass FMultiViewRenderingDevice::GetViewPassForIndex(bool bStereoRequested, uint32 ViewIndex) const
{
	if (!bStereoRequested)
		return eSSP_FULL;

	return (EStereoscopicPass)(eSSP_LEFT_EYE + ViewIndex);
}

uint32 FMultiViewRenderingDevice::GetViewIndexForPass(EStereoscopicPass StereoPassType) const
{
	switch (StereoPassType)
	{
	case eSSP_FULL:
		return 0;
	default:
		return StereoPassType - eSSP_LEFT_EYE;
	}
}

void FMultiViewRenderingDevice::AdjustViewRect(EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const
{
	SizeX = SizeX / nScreen;
	X += SizeX * (StereoPass - eSSP_LEFT_EYE);
}

int32 FMultiViewRenderingDevice::GetDesiredNumberOfViews(bool bStereoRequested) const
{
	return bStereoRequested ? nScreen : 1;
}

void FMultiViewRenderingDevice::CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation)
{
	float ScreenFOV = 45;
	float ScreenPadding = 0;
	UMultiViewRenderingSettings* Settings = GetMutableDefault<UMultiViewRenderingSettings>();
	if (Settings)
	{
		ScreenFOV = Settings->ScreenFOV;
		ScreenPadding = 2.0f * Settings->Bezel / Settings->ScreenWidth * ScreenFOV;
	}

	float RotationMultiplier = StereoPassType - eSSP_RIGHT_EYE;

	FVector dir = ViewRotation.Vector();
	FVector up = ViewRotation.RotateVector(FVector::UpVector);
	FVector dir2 = dir.RotateAngleAxis((ScreenFOV + ScreenPadding) * RotationMultiplier, up);

	ViewRotation = FRotationMatrix::MakeFromXZ(dir2, up).Rotator();

	// We assume that physical monitor width is 55 cm
	// For correct visual experience user should be at distance 47.63f (DistanceToMonitorFOV60) at FOV 60.
	// This code updates view location if user head is located on other distance from monitor
	/*const bool bUpdateLocation = true;
	if (bUpdateLocation)
	{
		const float DistanceFromViewerToMonitor = 66.0f; // in cm
		const float DistanceToMonitorFOV60 = 66;// *47.63f; // in cm
		//float CorrectionLength = (DistanceFromViewerToMonitor - DistanceToMonitorFOV60) / 100.0f * WorldToMeters;
		float CorrectionLength = (DistanceFromViewerToMonitor - DistanceToMonitorFOV60) * GNearClippingPlane / DistanceToMonitorFOV60;

		ViewLocation += (dir2 - dir) * CorrectionLength;
	}*/
}

FMatrix FMultiViewRenderingDevice::GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType) const
{
	float ScreenFOV = 45;
	UMultiViewRenderingSettings* Settings = GetMutableDefault<UMultiViewRenderingSettings>();
	if (Settings)
	{
		ScreenFOV = Settings->ScreenFOV;
	}

	const float HalfFov = FMath::DegreesToRadians(ScreenFOV) / 2.f;
	const float XS = 1.0f / FMath::Tan(HalfFov);
	const float YS = Aspect / FMath::Tan(HalfFov);
	const float NearZ = GNearClippingPlane;

	return FMatrix(
		FPlane(XS, 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, YS, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, 0.0f, 1.0f),
		FPlane(0.0f, 0.0f, NearZ, 0.0f));
}

void FMultiViewRenderingDevice::InitCanvasFromView(FSceneView* InView, UCanvas* Canvas)
{}

void FMultiViewRenderingDevice::RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef BackBuffer, FTexture2DRHIParamRef SrcTexture, FVector2D WindowSize) const
{
	check(IsInRenderingThread());

	FRHIRenderPassInfo RPInfo(BackBuffer, ERenderTargetActions::Clear_Store);
	RHICmdList.BeginRenderPass(RPInfo, TEXT("RenderTexture_RenderThread"));
	RHICmdList.EndRenderPass();

	const uint32 ViewportWidth = BackBuffer->GetSizeX();
	const uint32 ViewportHeight = BackBuffer->GetSizeY();
	RHICmdList.SetViewport(0, 0, 0, ViewportWidth, ViewportHeight, 1.0f);
}