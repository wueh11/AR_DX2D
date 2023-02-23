#include "yaMaterial.h"

namespace ya::graphics
{
	Material::Material()
		: Resource(eResourceType::Material)
		, mMode(eRenderingMode::Opaque)
	{
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::SetData(eGPUParam param, void* data)
	{
		switch (param)
		{
		case ya::graphics::eGPUParam::Int:
			mCB.iData = *static_cast<int*>(data);
			break;
		case ya::graphics::eGPUParam::Float:
			mCB.fData = *static_cast<float*>(data);
			break;
		case ya::graphics::eGPUParam::Vector2:
			mCB.xy = *static_cast<Vector2*>(data);
			break;
		case ya::graphics::eGPUParam::Vector3:
			mCB.xyz = *static_cast<Vector3*>(data);
			break;
		case ya::graphics::eGPUParam::Vector4:
			mCB.xyzw = *static_cast<Vector4*>(data);
			break;
		case ya::graphics::eGPUParam::Matrix:
			mCB.matrix = *static_cast<Matrix*>(data);
			break;
		default:
			break;
		}
	}

	void Material::Bind()
	{
		if(mTexture)
			mTexture->BindShader(eShaderStage::PS, 0);

		ConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];
		pCB->Bind(&mCB);
		pCB->SetPipeline(eShaderStage::VS);
		pCB->SetPipeline(eShaderStage::PS);
		
		mShader->Binds();
	}

	void Material::Clear()
	{
		/// 그림을 그려준후 버퍼에 남아있는 텍스쳐를 비워준다.
		mTexture->Clear();
	}

}