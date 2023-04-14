#include "yaStructedBuffer.h"
#include "yaGraphicDevice_DX11.h"

namespace ya::graphics
{
	StructedBuffer::StructedBuffer()
		: mSRV(nullptr)
		, mType(eSRVType::SRV)
		, mSize(0)
		, mStride(0)
		, mSRVSlot(0)
		, mUAVSlot(0)
		, mWriteBuffer(nullptr)
		, mReadBuffer(nullptr)
	{
	}

	StructedBuffer::~StructedBuffer()
	{
	}

	bool StructedBuffer::Create(size_t size, UINT stride, eSRVType type, void* data, bool cpuAccess)
	{
		mType = type;
		mSize = size;
		mStride = stride;

		setDiscription();
		createBuffer(data);
		createView();
		
		if (cpuAccess)
		{
			createRWBuffer();
		}

		return true;
	}

	void StructedBuffer::SetData(void* data, UINT bufferCount)
	{
		if (mStride < bufferCount) /// 버퍼의 크기가 더 클 경우에 버퍼의크기로 생성
			Create(mSize, bufferCount, eSRVType::SRV, data);
		else
			GetDevice()->SetData(mWriteBuffer.Get(), data, mSize * bufferCount); /// 데이터 셋팅을 mWriteBuffer에 한다

		GetDevice()->CopyResource(buffer.Get(), mWriteBuffer.Get());
	}

	void StructedBuffer::GetData(void* data, UINT size)
	{
		GetDevice()->CopyResource(mReadBuffer.Get(), buffer.Get());

		// readBuffer -> system memory 
		if (size == 0)
			GetDevice()->SetData(mReadBuffer.Get(), data, mSize * mStride); /// 사이즈 0일경우 내 버퍼사이즈로 셋팅
		else
			GetDevice()->SetData(mReadBuffer.Get(), data, size);
	}

	void StructedBuffer::BindSRV(eShaderStage stage, UINT slot)
	{
		mSRVSlot = slot;
		GetDevice()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
	}

	void StructedBuffer::BindUAV(eShaderStage stage, UINT slot)
	{
		mUAVSlot = slot;
		UINT i = -1;
		GetDevice()->BindUnorderedAccessView(slot, 1, mUAV.GetAddressOf(), &i);
	}

	void StructedBuffer::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::VS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, mSRVSlot, &srv);

		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccessView(mUAVSlot, 1, &uav, &i);
	}

	void StructedBuffer::setDiscription()
	{
		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; /// 구조버퍼로 만든것을 선언

		if (mType == eSRVType::UAV)
		{
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS; ///uav는 두개 flag를 사용해야한다(srv와 uav동시에
		}
		else if (mType == eSRVType::SRV)
		{
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		}
	}

	bool StructedBuffer::createBuffer(void* data)
	{
		if (data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = data;

			if (!(GetDevice()->CreateBuffer(&desc, &tSub, buffer.GetAddressOf())))
				return false;
		}
		else
		{
			if (!(GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
				return false;
		}

		return true;
	}

	bool StructedBuffer::createView()
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;

		if (mType == eSRVType::UAV)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Buffer.NumElements = mStride;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			if (!(GetDevice()->CreateUnorderedAccessView(buffer.Get(), &uavDesc, mUAV.GetAddressOf())))
				return false;
		}

		return false;
	}

	bool StructedBuffer::createRWBuffer()
	{
		D3D11_BUFFER_DESC wDesc = { desc };
		wDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; /// 구조화버퍼
		wDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		wDesc.Usage = D3D11_USAGE_DYNAMIC;
		wDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!(GetDevice()->CreateBuffer(&wDesc, nullptr, mWriteBuffer.GetAddressOf())))
			return false;

		D3D11_BUFFER_DESC rDesc = { desc };
		wDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		wDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		wDesc.Usage = D3D11_USAGE_DEFAULT;
		wDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		if (!(GetDevice()->CreateBuffer(&rDesc, nullptr, mReadBuffer.GetAddressOf())))
			return false;

		return true;
	}
}