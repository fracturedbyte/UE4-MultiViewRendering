#include "MultiViewLocalPlayer.h"
#include "MultiViewRenderingDevice.h"

UMultiViewLocalPlayer::UMultiViewLocalPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void UMultiViewLocalPlayer::PostInitProperties()
{
	if (GEngine)
	{
		GEngine->StereoRenderingDevice = TSharedPtr<IStereoRendering, ESPMode::ThreadSafe>(static_cast<IStereoRendering*>(new FMultiViewRenderingDevice));
	}

	Super::PostInitProperties();
}