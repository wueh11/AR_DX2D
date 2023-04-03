#pragma once
#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "yaResource.h"
#include "yaGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib") 
#else
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib") 
#endif

using namespace ya::enums;
namespace ya::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		bool Create(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShaderResource(eShaderStage stage, UINT slot);
		void LoadFile(const std::wstring& path);
		void InitializeResource();
		
		void BindUnorderedAccessView(UINT startSlot);
		void ClearUnorderedAccessView(UINT startSlot);
		
		void Clear();
		static void Clear(UINT startSlot);

		size_t GetHeight() { return mDesc.Height;  }
		size_t GetWidth() { return mDesc.Width;  }

		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV() { return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return mRTV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return mUAV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return mSRV; }

		//void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { mTexture = texture; }

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV; /// 뎁스스텐실에 접근하기위한 view
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV; /// 텍스쳐 만들때 사용하는 뷰. 쓰기가 가능해짐
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;

		D3D11_TEXTURE2D_DESC mDesc;
	};
}

