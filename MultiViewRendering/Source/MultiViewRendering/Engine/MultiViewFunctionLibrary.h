#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultiViewFunctionLibrary.generated.h"

UCLASS()
class MULTIVIEWRENDERING_API UMultiViewFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = MultiView, meta = (Keywords = "multi view"))
	static bool SetupTripleScreenWindow();

	UFUNCTION(BlueprintCallable, Category = MultiView, meta = (Keywords = "multi view"))
	static bool IsTripleScreenSetup();

	UFUNCTION(BlueprintCallable, Category = MultiView, meta = (Keywords = "multi view"))
	static bool EnableTripleScreenRendering(bool bEnable = true);

	static FPlatformRect GetVirtualDisplayRect();
};