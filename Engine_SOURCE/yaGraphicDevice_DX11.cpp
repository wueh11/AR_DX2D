#include "yaGraphicDevice_DX11.h"
#include "yaApplication.h"
#include "yaRenderer.h"
#include "yaMesh.h"
#include "yaConstantBuffer.h"
#include "yaTexture.h"

extern ya::Application application;

namespace ya::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11(ValidationMode validationMode)
	{
		graphics::GetDevice() = this;

		/// <summary>
		/// 1. Device 와 SwapChain 생성
		/// 2. 백버퍼에 실제로 렌더링할 렌더타겟뷰를 생성해줘야 한다.
		/// 3. 화면을 클리어 해줘야한다. 뷰포트를 생성해줘야 한다.
		/// 4. 매 프레임마다 위에서 생성한 렌더타겟뷰에 렌더링해줘야 한다.
		/// 5. SwapChain을 이용하여 최종 디바이스(디스플레이)에 화면을 그려줘야 한다.
		/// </summary>
		/// <param name="validationMode"></param>
		/// 
		HWND hwnd = application.GetHwnd();

		// Device, Device Context 초기화
		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG;	///debug로 만들어야 디버깅이 가능
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		ID3D11Device* pDevice = nullptr;
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, DeviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf()
			, &FeatureLevel
			, mContext.GetAddressOf());

		// SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {}; /// swap chain을 만드는데 필요한 description 
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = true; /// 전체화면
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; /// ->최종적으로 화면에 그려질 대상(백버퍼 렌더타겟)
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight(); /// 렌더타겟 크기
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; /// 픽셀의 데이터 포맷
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 240; /// 주사율
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; /// ->스케일안함

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
			return;

		mRenderTargetTexture = std::make_shared<Texture>();
		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget;

		// Get rendertarget for swapchain
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)renderTarget.GetAddressOf());

		mRenderTargetTexture->Create(renderTarget);


		D3D11_TEXTURE2D_DESC depthBuffer = {};
		depthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBuffer.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthBuffer.CPUAccessFlags = 0;

		depthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBuffer.Width = application.GetWidth();
		depthBuffer.Height = application.GetHeight();
		depthBuffer.ArraySize = 1;

		depthBuffer.SampleDesc.Count = 1;
		depthBuffer.SampleDesc.Quality = 0;

		depthBuffer.MipLevels = 0; /// 밉맵레벨
		depthBuffer.MiscFlags = 0;

		mDepthStencilBufferTexture = std::make_shared<Texture>();
		mDepthStencilBufferTexture->Create(depthBuffer.Width, depthBuffer.Height, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL);

		// Depth Stencil Buffer
		if (!CreateTexture(&depthBuffer, mDepthStencilBufferTexture->GetTexture().GetAddressOf()))
			return;

		// Depth Stencil Buffer View
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBufferTexture->GetTexture().Get(), nullptr, mDepthStencilBufferTexture->GetDSV().GetAddressOf())))
			return;

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewport = { 0.0f, 0.0f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.0f, 1.0f };
		BindViewports(&mViewport);
		mContext->OMSetRenderTargets(1, mRenderTargetTexture->GetRTV().GetAddressOf(), mDepthStencilBufferTexture->GetDSV().Get());
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
		renderer::Release();
	}

	bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
			return false;

		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
			return false;

		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), desc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTextrue2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTextrue2D)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(desc, NumElements, byteCode, bytecodeLength, ppInputLayout)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer)
	{
		// System -> GPU /// 램에 있던 정보를 GPU에 보낸다 input assembler
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
	{
		if (FAILED(mDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		if (FAILED(mDevice->CreateRenderTargetView(pResource, pDesc, ppRTView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
	{
		if (FAILED(mDevice->CreateShaderResourceView(pResource, pDesc, ppSRView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
	{

		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader)
	{ /// GPGPU
		if (FAILED(mDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(pBlendStateDesc, ppBlendState)))
			return false;
		return true;
	}

	void GraphicDevice_DX11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		mContext->IASetPrimitiveTopology(topology);
	}

	void GraphicDevice_DX11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}

	void GraphicDevice_DX11::BindVertexBuffer(UINT startSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(startSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}

	void GraphicDevice_DX11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, format, offset);
	}

	void GraphicDevice_DX11::BindVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice_DX11::BindPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice_DX11::BindComputeShader(ID3D11ComputeShader* pComputeShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice_DX11::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
	{
		mContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
	}

	void GraphicDevice_DX11::BindViewports(D3D11_VIEWPORT* viewport)
	{
		mContext->RSSetViewports(1, viewport);
	}

	void GraphicDevice_DX11::BindUnorderedAccessView(UINT startSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
	{
		mContext->CSSetUnorderedAccessViews(startSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
	}

	void GraphicDevice_DX11::BindShaderResource(eShaderStage stage, UINT slot, ID3D11ShaderResourceView* const* ppShaderResourceViews)
	{
		switch (stage)
		{
		case ya::graphics::eShaderStage::VS:
			mContext->VSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case ya::graphics::eShaderStage::HS:
			mContext->HSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case ya::graphics::eShaderStage::DS:
			mContext->DSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case ya::graphics::eShaderStage::GS:
			mContext->GSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case ya::graphics::eShaderStage::PS:
			mContext->PSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case ya::graphics::eShaderStage::CS:
			mContext->CSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::BindBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		/// 상수버퍼에 데이터를 묶어두는 역할
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
		/// sub에 데이터를 매핑, 메모리 복사 후 언매핑으로 해제
	}

	void GraphicDevice_DX11::BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case ya::graphics::eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer); //type->슬롯
			break;
		case ya::graphics::eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::BindSamplers(eShaderStage stage, UINT slot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		switch (stage)
		{
		case ya::graphics::eShaderStage::VS:
			mContext->VSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case ya::graphics::eShaderStage::HS:
			mContext->HSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case ya::graphics::eShaderStage::DS:
			mContext->DSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case ya::graphics::eShaderStage::GS:
			mContext->GSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case ya::graphics::eShaderStage::PS:
			mContext->PSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case ya::graphics::eShaderStage::CS:
			mContext->CSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::BindsSamplers(UINT slot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		mContext->VSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->HSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->DSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->GSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->PSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->CSSetSamplers(slot, NumSamplers, ppSamplers);
	}

	void GraphicDevice_DX11::BindRasterizerState(ID3D11RasterizerState* pRasterizerState)
	{
		mContext->RSSetState(pRasterizerState);
	}

	void GraphicDevice_DX11::BindDepthStencilState(ID3D11DepthStencilState* pDepthstencilState)
	{
		mContext->OMSetDepthStencilState(pDepthstencilState, 0);
	}

	void GraphicDevice_DX11::BindBlendState(ID3D11BlendState* pBlendState)
	{
		mContext->OMSetBlendState(pBlendState, nullptr, 0xffffffff);
	}

	void GraphicDevice_DX11::Clear()
	{
		// clear render target
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetTexture->GetRTV().Get(), backgroundColor);
		mContext->ClearDepthStencilView(mDepthStencilBufferTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void GraphicDevice_DX11::AdjustViewPorts()
	{
		// resize viewport
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect); /// 클라이언트 좌표를 가져옴
		mViewport = {
			0.0f, 0.0f	 /// 위치
			, FLOAT(winRect.right - winRect.left) , FLOAT(winRect.bottom - winRect.top) ///크기
			, 0.0f, 1.0f	/// 깊이값
		};
		BindViewports(&mViewport);
		mContext->OMSetRenderTargets(1, mRenderTargetTexture->GetRTV().GetAddressOf(), mDepthStencilBufferTexture->GetDSV().Get());
	}

	void GraphicDevice_DX11::Draw()
	{
		mContext->Draw(0, 0);
	}

	void GraphicDevice_DX11::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT baseVertexLocation)
	{
		mContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
	}

	void GraphicDevice_DX11::Present()
	{
		// 백버퍼에 그려준다
		mSwapChain->Present(0, 0); /// swapchain 으로 그려줌
	}
}