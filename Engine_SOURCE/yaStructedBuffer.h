#pragma once
#include "yaGraphics.h"

namespace ya::graphics
{
	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		virtual ~StructedBuffer();

		bool Create(size_t size, UINT stride, eSRVType type, void* data);
		void SetData(void* data, UINT bufferCount);
		void Bind(eShaderStage stage, UINT slot);

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;
	};
}

