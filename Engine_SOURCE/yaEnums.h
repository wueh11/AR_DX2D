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
		Monster,
		Player,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,
		MeshRenderer,
		SpriteRenderer,
		Animator,
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

	/*struct Ray
	{
		Vector3 origin;
		Vector3 dest;
	};*/
}