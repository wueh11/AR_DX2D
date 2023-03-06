#pragma once
//#include "CommonInclude.h"
#include <wrl.h>
#include "yaMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

/// 상수버퍼 생성
#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name
/// 치환된 name으로 변수값을 생성해주는 매크로
/// allignas -> 무조건 정해준 크기로 구조체 할당

/// 슬롯 번호 지정
#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2

namespace ya::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		Count,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End,
	};

	enum class eRSType /// Rasterizer
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone, /// 선만
		End,
	};

	enum class eDSType // Depth Stencil 깊이 비교
	{
		Less, /// 작앗을때 그리는것
		Greater, 
		NoWrite, ///깊이버퍼사용X (무조건 레이어순서대로 그려준다)
		None,
		End,
	};

	enum class eBSType /// BlendState
	{
		Default, /// 블렌드 X
		AlphaBlend, /// 투명처리
		OneOne, /// 물체 색을 더한다
		End,
	};

	enum class eRenderingMode
	{
		Opaque, /// 투명하지 않은 물체
		CutOut, /// 부분적으로 투명
		Transparent,
		End,
	};

	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		End,
	};

	enum class eGPUParam
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix,

	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;
		float radius;
		float duration;
		float time;
	};
}