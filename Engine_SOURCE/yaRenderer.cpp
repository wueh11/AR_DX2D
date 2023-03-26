#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"
#include "yaPaintShader.h"

namespace ya::renderer
{
	//정점 데이터
	Vertex vertexes[4] = {};
	
	//상수 버퍼
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	StructedBuffer* lightsBuffer = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End]; /// 씬마다 사용하는 카메라 설정
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;

	void LoadMesh() 
	{
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Create Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);

		// Vertex Buffer
		mesh->CreateVertexBuffer(vertexes, 4);

		// Index Buffer
		std::vector<UINT> indexes;
		indexes = { 0, 1, 2, 0, 2, 3, 0 };
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//Debug Rect
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		std::shared_ptr<Mesh> debugMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugMesh);
		debugMesh->CreateVertexBuffer(vertexes, 4);
		debugMesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Mesh
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		int iSlice = 60; /// 원을 구성할 점을 몇개로 구성할지(center 점으로부터 정점);
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;	/// 점과 점 사이 각도

		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}

		indexes.clear();
		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back(i + 1); /// 중앙center 제외하고 원테두리부터 시작
		}
		indexes.push_back(1); /// 원에서 원으로 끝나도록

		std::shared_ptr<Mesh> circleMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", circleMesh);
		circleMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		circleMesh->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void LoadShader()
	{
		/*** Input Layout 설정 ***/

#pragma region Input layout description
		//Input Layout (정점 구조 정보)
		/// 속성들을 메모리에 넣는 방법을 정의

		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {}; /// [2]-> Vector3 Pos, Vector4 Color 두가지 정보이기 때문에

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; ///12byte(float3)
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION"; ///hlsl과 이름 맞춰줘야함
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16; /// arrLayout[0]의 크기가 12이므로 arrLayout[1]은 12부터 시작
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; ///16byte(float4)
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR"; ///hlsl과 이름 맞춰줘야함
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;
#pragma endregion

		{ // Default
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
			shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
			Resources::Insert<Shader>(L"TriangleShader", shader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, shader->GetVSBlobBufferPointer()
				, shader->GetVSBlobBufferSize()
				, shader->GetInputLayoutAddressOf());
		}

		{ // Default
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			shader->Create(eShaderStage::VS, L"RectVS.hlsl", "main");
			shader->Create(eShaderStage::PS, L"RectPS.hlsl", "main");
			Resources::Insert<Shader>(L"RectShader", shader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, shader->GetVSBlobBufferPointer()
				, shader->GetVSBlobBufferSize()
				, shader->GetInputLayoutAddressOf());
		}

		{ // Sprite
			std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
			spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
			spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
			Resources::Insert<Shader>(L"SpriteShader", spriteShader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, spriteShader->GetVSBlobBufferPointer()
				, spriteShader->GetVSBlobBufferSize()
				, spriteShader->GetInputLayoutAddressOf());
		}

		{ // nosolidNone
			std::shared_ptr<Shader> spriteSolidNoneShader = std::make_shared<Shader>();
			spriteSolidNoneShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
			spriteSolidNoneShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
			spriteSolidNoneShader->SetRSState(eRSType::SolidNone);
			Resources::Insert<Shader>(L"SpriteSolidNoneShader", spriteSolidNoneShader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, spriteSolidNoneShader->GetVSBlobBufferPointer()
				, spriteSolidNoneShader->GetVSBlobBufferSize()
				, spriteSolidNoneShader->GetInputLayoutAddressOf());
		}
		
		{ // UI
			std::shared_ptr<Shader> UIshader = std::make_shared<Shader>();
			UIshader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
			UIshader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");
			Resources::Insert<Shader>(L"UIShader", UIshader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, UIshader->GetVSBlobBufferPointer()
				, UIshader->GetVSBlobBufferSize()
				, UIshader->GetInputLayoutAddressOf());
		}
		
		{ // Grid Shader
			std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
			gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
			gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
			gridShader->SetRSState(eRSType::SolidNone); /// 컬링되면 안됨(그리드라 항상 나와야함)
			gridShader->SetDSState(eDSType::NoWrite); /// 영향을 받으면 안됨
			gridShader->SetBSState(eBSType::AlphaBlend);
			Resources::Insert<Shader>(L"GridShader", gridShader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, gridShader->GetVSBlobBufferPointer()
				, gridShader->GetVSBlobBufferSize()
				, gridShader->GetInputLayoutAddressOf());
		}

		{ // Fade Shader
			std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
			fadeShader->Create(eShaderStage::VS, L"FadeVS.hlsl", "main");
			fadeShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");
			fadeShader->SetRSState(eRSType::SolidNone);	/// 컬링
			fadeShader->SetDSState(eDSType::NoWrite);	/// 깊이버퍼
			fadeShader->SetBSState(eBSType::AlphaBlend);
			Resources::Insert<Shader>(L"FadeShader", fadeShader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, fadeShader->GetVSBlobBufferPointer()
				, fadeShader->GetVSBlobBufferSize()
				, fadeShader->GetInputLayoutAddressOf());
		}

		{ // Debug Shader
			std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
			debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
			debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
			debugShader->SetRSState(eRSType::SolidNone);
			debugShader->SetDSState(eDSType::NoWrite);
			debugShader->SetBSState(eBSType::AlphaBlend);
			debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
			Resources::Insert<Shader>(L"DebugShader", debugShader);

			GetDevice()->CreateInputLayout(arrLayoutDesc, 3
				, debugShader->GetVSBlobBufferPointer()
				, debugShader->GetVSBlobBufferSize()
				, debugShader->GetInputLayoutAddressOf());
		}

		{ // PaintShader
			std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
			paintShader->Create(L"PaintCS.hlsl", "main");
			Resources::Insert<PaintShader>(L"PaintShader", paintShader);
		}
	}

	void SetUpState()
	{
#pragma region Sampler State
		{ // Sampler State
			D3D11_SAMPLER_DESC samplerDesc = {};
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;

			samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
			GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

			samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
			GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

			samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
			GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());

			GetDevice()->BindsSamplers((UINT)eSamplerType::Point, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
			GetDevice()->BindsSamplers((UINT)eSamplerType::Linear, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());
			GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		}
#pragma endregion

#pragma region Rasterizer State
		{
			D3D11_RASTERIZER_DESC rsDesc = {};
			rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

			GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

			rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
			GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

			rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
			GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

			rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
			rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
			GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
		}
#pragma endregion

#pragma region Depth Stencil State
		{
			D3D11_DEPTH_STENCIL_DESC dsDesc = {};
			dsDesc.DepthEnable = true;
			dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL; /// 어떤 방식으로 비교하는지
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			dsDesc.StencilEnable = false;

			GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

			dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
			GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

			dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
			GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

			dsDesc.DepthEnable = false;
			dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
			dsDesc.StencilEnable = false;

			GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
		}
#pragma endregion

#pragma region Blend State
		{
			blendStates[(UINT)eBSType::Default] = nullptr;

			D3D11_BLEND_DESC bsDesc = {};
			bsDesc.AlphaToCoverageEnable = false;
			bsDesc.IndependentBlendEnable = false;
			bsDesc.RenderTarget[0].BlendEnable = true;
			bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
			bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
			bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

			bsDesc.AlphaToCoverageEnable = false;
			bsDesc.IndependentBlendEnable = false;

			bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
			bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

			GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
		}
#pragma endregion
	}

	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		//Structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::None, nullptr);
	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"image", L"image.jpg");
		Resources::Load<Texture>(L"HPBar", L"HPBar.png");
		Resources::Load<Texture>(L"noise", L"noise2.png");

		{ // uavTexture
			std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
			uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
			Resources::Insert<Texture>(L"PaintTexture", uavTexture);
		}

		{ //character
			Resources::Load<Texture>(L"isaac", L"Issac\\character_001_isaac.png");
			Resources::Load<Texture>(L"tearpoofa", L"Issac\\effect_015_tearpoofa.png");
			Resources::Load<Texture>(L"bomb", L"Issac\\pickup_016_bomb.png");
			Resources::Load<Texture>(L"explosion", L"Issac\\effect_029_explosion.png");
		}

		{ // uis
			Resources::Load<Texture>(L"hudpickups", L"Issac\\hudpickups.png");
			Resources::Load<Texture>(L"ui_hearts", L"Issac\\ui_hearts.png");
			Resources::Load<Texture>(L"ui_chargebar", L"Issac\\ui_chargebar.png");
			Resources::Load<Texture>(L"ui_cardspills", L"Issac\\ui_cardspills.png");
			Resources::Load<Texture>(L"ui_cardfronts", L"Issac\\ui_cardfronts.png");
			Resources::Load<Texture>(L"minimap1", L"Issac\\minimap1.png");
		}

		{ // title
			Resources::Load<Texture>(L"titlemenu", L"Issac\\titlemenu.png");
			Resources::Load<Texture>(L"gamemenu", L"Issac\\gamemenu.png");
			Resources::Load<Texture>(L"charactermenu", L"Issac\\charactermenu.png");
			Resources::Load<Texture>(L"menuoverlay", L"Issac\\menuoverlay.png");
			Resources::Load<Texture>(L"menushadow", L"Issac\\menushadow.png");
			Resources::Load<Texture>(L"splashes", L"Issac\\splashes.png");
		}

		{ // room
			Resources::Load<Texture>(L"bgblack", L"Issac\\bgblack.png");
			Resources::Load<Texture>(L"shading", L"Issac\\shading.png");
		}

		{ //basement
			Resources::Load<Texture>(L"basement", L"Issac\\01_basement.png");
			Resources::Load<Texture>(L"controls", L"Issac\\controls.png");
		}
	}

	void LoadMaterial()
	{
		{ // computeshader
			std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"PaintTexture");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			Resources::Insert<Material>(L"CSMaterial", material);
		}

		{ // Image
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"image");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			Resources::Insert<Material>(L"RectMaterial", material);
		}

		{ // Sprite
			std::shared_ptr<Texture> spriteTexture = Resources::Find<Texture>(L"image");
			std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(spriteTexture);
			Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);
		}

		{ // grid
			std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
			std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
			gridMaterial->SetShader(gridShader);
			Resources::Insert<Material>(L"GridMaterial", gridMaterial);
		}

		{ // Fade
			std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
			std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();
			fadeMaterial->SetShader(fadeShader);
			Resources::Insert<Material>(L"FadeMaterial", fadeMaterial);
		}

		{ // Debug
			std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
			std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
			debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
			debugMaterial->SetShader(debugShader);
			Resources::Insert<Material>(L"DebugMaterial", debugMaterial);
		}

		std::shared_ptr<Shader> rectShader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Shader> spriteSolidNoneShader = Resources::Find<Shader>(L"SpriteSolidNoneShader");

		////////////////
		{ // Issac
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"isaac");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(spriteSolidNoneShader);
			material->SetTexture(texture);
			Resources::Insert<Material>(L"isaacMaterial", material);
		}

		{ // tearpoofa
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"tearpoofa");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(spriteShader);
			material->SetTexture(texture);
			Resources::Insert<Material>(L"tearpoofaMaterial", material);
		}

		{ // bomb
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"bomb");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			material->SetTexture(texture);
			Resources::Insert<Material>(L"bombMaterial", material);
		}
		
		{ // bomb
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"explosion");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			material->SetTexture(texture);
			Resources::Insert<Material>(L"explosionMaterial", material);
		}

		{ // title
			{ //titleBG
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"titlemenu");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"titlemenuMaterial", material);
			}

			{ //splashes
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"splashes");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"splashesMaterial", material);
			}

			{ //gamemenu
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"gamemenu");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"gamemenuMaterial", material);
			}

			{ //charactermenu
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"charactermenu");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"charactermenuMaterial", material);
			}

			{ //menuoverlay
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"menuoverlay");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetShader(rectShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert<Material>(L"menuoverlayMaterial", material);
			}

			{ //menushadow
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"menushadow");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetShader(rectShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"menushadowMaterial", material);
			}
		}

		{ // uis
			{ //hudpickups
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"hudpickups");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"hudpickupsMaterial", material);
			}

			{ //ui_hearts
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"ui_hearts");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"ui_heartsMaterial", material);
			}

			{ //ui_chargebar
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"ui_chargebar");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"ui_chargebarMaterial", material);
			}

			{ //ui_cardspills
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"ui_cardspills");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"ui_cardspillsMaterial", material);
			}

			{ //ui_cardfronts
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"ui_cardfronts");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"ui_cardfrontsMaterial", material);
			}

			{ //minimap1
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"minimap1");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"minimap1Material", material);
			}

		}

		{ // rooms
			{ //bgblack
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"bgblack");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(rectShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"bgblackMaterial", material);
			}
			{ //shading
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"shading");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(rectShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"shadingMaterial", material);
			}
		}

		{ // basement
			{ //BG_basement
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"basement");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetShader(spriteSolidNoneShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"basementMaterial", material);
			}
			{ //controls
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"controls");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(rectShader);
				material->SetTexture(texture);
				Resources::Insert<Material>(L"controlsMaterial", material);
			}
		}

	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Render()
	{
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{ /// 실시간으로 빛이 계속 추가될 수 있으므로 push 생성
		lightsBuffer->Bind(lights.data(), lights.size());
		lightsBuffer->SetPipeline(eShaderStage::VS, 13);
		lightsBuffer->SetPipeline(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLight = lights.size(); /// 빛의 전체 개수를 저장한다

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->Bind(&trCb);
		cb->SetPipeline(eShaderStage::VS);
		cb->SetPipeline(eShaderStage::PS);
	}
}