#pragma once
//#include "CommonInclude.h"
#include <wrl.h>
#include "yaMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

/// ������� ����
#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name
/// ġȯ�� name���� �������� �������ִ� ��ũ��
/// allignas -> ������ ������ ũ��� ����ü �Ҵ�

/// ���� ��ȣ ����
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
		WireframeNone, /// ����
		End,
	};

	enum class eDSType // Depth Stencil ���� ��
	{
		Less, /// �۾����� �׸��°�
		Greater, 
		NoWrite, ///���̹��ۻ��X (������ ���̾������� �׷��ش�)
		None,
		End,
	};

	enum class eBSType /// BlendState
	{
		Default, /// ���� X
		AlphaBlend, /// ����ó��
		OneOne, /// ��ü ���� ���Ѵ�
		End,
	};

	enum class eRenderingMode
	{
		Opaque, /// �������� ���� ��ü
		CutOut, /// �κ������� ����
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