#include "MultiViewRenderingSettings.h"

UMultiViewRenderingSettings::UMultiViewRenderingSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

float UMultiViewRenderingSettings::GetScreenFOV() const
{
	if (bUseScreenFov)
	{
		return ScreenFOV;
	}
	else
	{
		return 2.0f * 180.0f / PI * FMath::Atan2(0.5f * ScreenWidth, DistanceFromScreenToPlayer);
	}
}