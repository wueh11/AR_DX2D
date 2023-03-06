#pragma once
#include "yaComponent.h"

namespace ya
{
	using namespace math;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective, /// 직교투영
			Orthographic,
		};
	public:
		__forceinline static Matrix& GetGpuViewMatrix() { return View; }
		__forceinline static Matrix& GetGpuProjectionMatrix() { return Projection; }
		__forceinline static void SetGpuViewMatrix(Matrix view) { View = view; }
		__forceinline static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

		Camera();
		virtual ~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType layer, bool enable = true); /// 원하는 비트 위치 값 설정
		void EnableLayerMasks() { mLayerMasks.set(); } /// 전부 true 
		void DisableLayerMasks() { mLayerMasks.reset(); }/// 전부 false 

		void SetProjectionType(eProjectionType type) { mType = type; }
		Matrix& GetViewMatrix() { return mView; }
		Matrix& GetProjectionMatrix() { return mProjection; }

	private:
		void SortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void PushGameObjectToRenderingModes(GameObject* gameObject);

	public:
		float GetScale() { return mScale; }

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio; /// 종횡비
		
		float mNear;	/// 가까이 있는 값
		float mFar;		/// 최대 멀리 있는 값
		float mScale;	/// 확대

		std::bitset<(UINT)eLayerType::End> mLayerMasks; /// 배열처럼 사용하면서 메모리는 1bit씩 사용

		/// 동일한 Z일 경우 물체(투명, 불투명..)를 그려주는 순서를 나눠줘야함.
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

	};
}

