#pragma once

#include "Engine/LocalPlayer.h"
#include "MultiViewLocalPlayer.generated.h"

UCLASS(transient)
class MULTIVIEWRENDERING_API UMultiViewLocalPlayer : public ULocalPlayer
{
public:
	GENERATED_UCLASS_BODY()

	void PostInitProperties() override;
};