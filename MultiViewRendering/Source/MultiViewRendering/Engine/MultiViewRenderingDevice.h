#pragma once

class FMultiViewRenderingDevice : public IStereoRendering
{
public:
	FMultiViewRenderingDevice();
	virtual ~FMultiViewRenderingDevice();

	bool IsStereoEnabled() const override;
	bool EnableStereo(bool stereo = true) override;

	EStereoscopicPass GetViewPassForIndex(bool bStereoRequested, uint32 ViewIndex) const override;

	uint32 GetViewIndexForPass(EStereoscopicPass StereoPassType) const override;

	void AdjustViewRect(EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;

	int32 GetDesiredNumberOfViews(bool bStereoRequested) const override;

	void CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override;

	FMatrix GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType) const override;

	void InitCanvasFromView(FSceneView* InView, UCanvas* Canvas) override;

	void RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef BackBuffer, FTexture2DRHIParamRef SrcTexture, FVector2D WindowSize) const override;

private:
	bool bStereoPossible = false;
	bool bStereoEnabled = true;

	float Aspect = 1920.0f / 1080.0f;
	int32 nScreen = 3;
	float FOV = 60; // It looks like it is the best value for triple screen
};