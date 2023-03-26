#pragma once
#include "yaGraphics.h"
#include "yaResource.h"

namespace ya::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		~ComputeShader();

		virtual HRESULT Load(const std::wstring& path) override;

		bool Create(const std::wstring& file, const std::string& funcName);
		void OnExcute();

		virtual void Binds();
		virtual void Clear();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob; /// 셰이더 코드를 이진파일로 가지고있음
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

		/// 스레드의 개수 지정
		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;

		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;

	};

}
