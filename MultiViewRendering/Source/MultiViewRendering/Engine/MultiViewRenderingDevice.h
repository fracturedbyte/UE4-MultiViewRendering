#pragma once

class FMultiViewRenderingDevice : public IStereoRendering
{
public:
	FMultiViewRenderingDevice()
	{}

	virtual ~FMultiViewRenderingDevice() {}

	bool IsStereoEnabled() const override { return true; }

	bool EnableStereo(bool stereo = true) override { return true; }

	EStereoscopicPass GetViewPassForIndex(bool bStereoRequested, uint32 ViewIndex) const override
	{
		if (!bStereoRequested)
			return EStereoscopicPass::eSSP_FULL;
		else if (ViewIndex == 0)
			return EStereoscopicPass::eSSP_LEFT_EYE;
		else if (ViewIndex == 1)
			return EStereoscopicPass::eSSP_RIGHT_EYE;
		else
			return EStereoscopicPass::eSSP_LEFT_EYE_SIDE;
	}

	virtual uint32 GetViewIndexForPass(EStereoscopicPass StereoPassType) const override
	{
		switch (StereoPassType)
		{
		case eSSP_LEFT_EYE:
		case eSSP_FULL:
			return 0;

		case eSSP_RIGHT_EYE:
			return 1;

		case eSSP_LEFT_EYE_SIDE:
			return 2;

		default:
			check(0);
			return -1;
		}
	}

	void AdjustViewRect(EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override
	{
		Aspect = SizeX / float(SizeY * nScreen);

		SizeX = SizeX / nScreen;
		X += SizeX * (StereoPass - eSSP_LEFT_EYE);
	}

	int32 GetDesiredNumberOfViews(bool bStereoRequested) const override { return (bStereoRequested) ? nScreen : 1; }

	void CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override
	{
		float RotationMultiplier = StereoPassType - eSSP_RIGHT_EYE;

		FVector dir = ViewRotation.Vector();
		FVector up = ViewRotation.RotateVector(FVector::UpVector);
		dir = dir.RotateAngleAxis(FOVInDegrees * RotationMultiplier, up);

		ViewRotation = FRotationMatrix::MakeFromXZ(dir, up).Rotator();
	}

	virtual FMatrix GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType) const override
	{
		const float HalfFov = FMath::DegreesToRadians(FOVInDegrees) / 2.f;
		const float XS = 1.0f / FMath::Tan(HalfFov);
		const float YS = Aspect / FMath::Tan(HalfFov);
		const float NearZ = GNearClippingPlane;

		return FMatrix(
			FPlane(XS, 0.0f, 0.0f, 0.0f),
			FPlane(0.0f, YS, 0.0f, 0.0f),
			FPlane(0.0f, 0.0f, 0.0f, 1.0f),
			FPlane(0.0f, 0.0f, NearZ, 0.0f));
	}

	virtual void InitCanvasFromView(FSceneView* InView, UCanvas* Canvas) override
	{
	}

	virtual void RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef BackBuffer, FTexture2DRHIParamRef SrcTexture, FVector2D WindowSize) const override
	{
		check(IsInRenderingThread());

		FRHIRenderPassInfo RPInfo(BackBuffer, ERenderTargetActions::Clear_Store);
		RHICmdList.BeginRenderPass(RPInfo, TEXT("RenderTexture_RenderThread"));
		RHICmdList.EndRenderPass();

		const uint32 ViewportWidth = BackBuffer->GetSizeX();
		const uint32 ViewportHeight = BackBuffer->GetSizeY();
		RHICmdList.SetViewport(0, 0, 0, ViewportWidth, ViewportHeight, 1.0f);
	}

	float FOVInDegrees = 60;
	int32 nScreen = 3;
	mutable float Aspect = 1.0f;
};
