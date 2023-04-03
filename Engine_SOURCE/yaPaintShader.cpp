#include "yaPaintShader.h"

namespace ya::graphics
{
	PaintShader::PaintShader()
		: ComputeShader()
		, mTarget(nullptr)
		, mTexture(nullptr)
	{
	}

	PaintShader::~PaintShader()
	{
	}
	
	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessView(0);

		if(mTexture != nullptr)
			mTexture->BindShaderResource(eShaderStage::CS, 0);

		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;

	}
	
	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessView(0);

		if (mTexture != nullptr)
			mTexture->Clear(0);
	}
}