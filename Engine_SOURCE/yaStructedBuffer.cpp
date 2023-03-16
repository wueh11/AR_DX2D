#include "yaStructedBuffer.h"
#include "yaGraphicDevice_DX11.h"

namespace ya::graphics
{
	StructedBuffer::StructedBuffer()
		: mSRV(nullptr)
		, mType(eSRVType::None)
		, mSize(0)
		, mStride(0)
	{
	}

	StructedBuffer::~StructedBuffer()
	{
	}

	bool StructedBuffer::Create(size_t size, UINT stride, eSRVType type, void* data)
	{
		mType = type;
		mSize = size;
		mStride = stride;

		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; /// 구조버퍼로 만든것을 선언

		if (data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = data;

			if (FAILED(GetDevice()->CreateBuffer(&desc, &tSub, buffer.GetAddressOf())))
				return false;
		}
		else
		{
			if (FAILED(GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
				return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (FAILED(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;

		return true;
	}

	void StructedBuffer::Bind(void* data, UINT bufferCount)
	{
		if (mStride < bufferCount) /// 버퍼의 크기가 더 클 경우에 버퍼의크기로 생성
			Create(mSize, bufferCount, eSRVType::None, data);
		else
			GetDevice()->BindBuffer(buffer.Get(), data, mSize * bufferCount);
	}

	void StructedBuffer::SetPipeline(eShaderStage stage, UINT slot)
	{
		GetDevice()->SetShaderResource(stage, slot, mSRV.GetAddressOf());
	}
}