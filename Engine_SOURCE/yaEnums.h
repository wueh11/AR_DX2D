#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Title,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Grid,
		Background,
		Camera,
		Effect,
		Monster,
		Player,
		Projectile,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Camera,
		Mesh,
		Collider,
		MeshRenderer,
		ImageRenderer,
		SpriteRenderer,
		Animator,
		Light,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab, /// ���� ������ ����(�������Ʈ)
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,

		///2D
		Rect,
		Circle,

		///3D
		Box,		
		Sphere,

		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,	/// �л걤
		Point,			/// ����
		Spot,
		End,
	};

	/*struct Ray
	{
		Vector3 origin;
		Vector3 dest;
	};*/
}