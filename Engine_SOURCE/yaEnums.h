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
		Transform, // 위치 데이터 수정하는 컴포넌트
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
		Prefab, /// 게임 데이터 저장(블루프린트)
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
		Directional,	/// 분산광
		Point,			/// 영역
		Spot,
		End,
	};

	/*struct Ray
	{
		Vector3 origin;
		Vector3 dest;
	};*/
}