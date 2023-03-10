#pragma once
#include "CommonInclude.h"
#include "yaMath.h"
#include "yaGraphicDevice_DX11.h"
#include "yaMesh.h"
#include "yaShader.h"

#include "yaConstantBuffer.h"
#include "yaCamera.h"

using namespace ya::math;
using namespace ya::graphics;
namespace ya::renderer
{
	/// 정점 정보
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATOR)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};

	//정점 데이터
	extern Vertex vertexes[4];

	// 상수 버퍼
	extern ConstantBuffer* constantBuffers[];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern Camera* mainCamera;
	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;

	void Initialize();
	void Render();
	void Release();
	
}