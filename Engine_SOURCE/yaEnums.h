#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Work,
		Title,
		Play,
		Basement1,
		Basement1Boss,
		Basement2,
		Basement2Boss,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Grid,
		Stage,
		Background,
		Wall,

		Floor,
		Land,
		Camera,
		Effect,
		Monster,
		Player,

		Item,
		Projectile,
		Particle,
		UI,

		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Rigidbody,
		Camera,
		Mesh,
		Collider,
		MeshRenderer,
		ImageRenderer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		AudioListener,
		AudioSource,
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
		AudioClip,
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