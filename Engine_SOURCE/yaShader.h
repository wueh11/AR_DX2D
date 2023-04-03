#pragma once
#include "yaResource.h"
#include "yaGraphics.h"

namespace ya
{
	using namespace graphics;
	class Shader : public Resource
	{
	public:
		Shader();
		virtual ~Shader();

		virtual HRESULT Load(const std::wstring& path);

		void Create(eShaderStage stage, const std::wstring& file, const std::string& funcName);
		void Binds();

		ID3D11InputLayout* GetInputLayout() { return mInputLayout.Get(); }
		ID3D11InputLayout** GetInputLayoutAddressOf() { return mInputLayout.GetAddressOf(); }

		void* GetVSBlobBufferPointer() { return mVSBlob->GetBufferPointer(); }
		SIZE_T GetVSBlobBufferSize() { return mVSBlob->GetBufferSize(); }

		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { mTopology = topology; }
		void SetRSState(eRSType state) { mRSType = state; }
		void SetDSState(eDSType state) { mDSType = state; }
		void SetBSState(eBSType state) { mBSType = state; }

	private:
		//��ǲ ���̾ƿ�(���� ����)
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout = nullptr;
		
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		eShaderStage mStage;
		
		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

		eRSType mRSType;
		eDSType mDSType;
		eBSType mBSType;

		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;
	};
}