#pragma once

#include "MultiViewRenderingSettings.generated.h"

UCLASS(config = Game, defaultconfig)
class UMultiViewRenderingSettings : public UObject
{
public:
	GENERATED_BODY()
	UMultiViewRenderingSettings(const FObjectInitializer& ObjectInitializer);

	// If total screen angle will be bigger or equal 180, it will not be possible to get advantage of shared cascades, in degrees
	UPROPERTY(EditAnywhere, config, Category = General)
	float ScreenFOV = 45;

	// Horizontal physical width, in mm
	UPROPERTY(EditAnywhere, config, Category = General)
	float ScreenWidth = 530;

	// Monitor border width (of one monitor), in mm
	UPROPERTY(EditAnywhere, config, Category = General)
	float Bezel = 10;

	// In mm
	UPROPERTY(EditAnywhere, config, Category = General)
	float DistanceFromScreenToPlayer = 550;
};