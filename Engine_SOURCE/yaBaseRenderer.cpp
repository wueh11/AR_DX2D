#include "yaBaseRenderer.h"

namespace ya
{
	BaseRenderer::BaseRenderer(eComponentType type)
		:Component(type)
		, mImageCb{}
		, mImageAlpha(0.0f)
	{
	}

	BaseRenderer::~BaseRenderer()
	{
	}

	void BaseRenderer::Initialize()
	{
	}

	void BaseRenderer::Update()
	{
	}

	void BaseRenderer::FixedUpdate()
	{
	}

	void BaseRenderer::Render()
	{
		renderer::ImageCB imageCb = {};
		imageCb.colorType = mColorType;
		imageCb.imageAlpha = mImageAlpha;
		imageCb.useRate = mbUseRate;
		imageCb.useRange = mbUseRange;
		imageCb.imageColor = mImageColor;
		imageCb.imageRange = mImageRange;
		imageCb.imageRate = mImageRate;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Image];
		cb->SetData(&imageCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
}