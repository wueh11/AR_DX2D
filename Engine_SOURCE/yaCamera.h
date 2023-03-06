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
			Perspective, /// ��������
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

		void TurnLayerMask(eLayerType layer, bool enable = true); /// ���ϴ� ��Ʈ ��ġ �� ����
		void EnableLayerMasks() { mLayerMasks.set(); } /// ���� true 
		void DisableLayerMasks() { mLayerMasks.reset(); }/// ���� false 

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
		float mAspectRatio; /// ��Ⱦ��
		
		float mNear;	/// ������ �ִ� ��
		float mFar;		/// �ִ� �ָ� �ִ� ��
		float mScale;	/// Ȯ��

		std::bitset<(UINT)eLayerType::End> mLayerMasks; /// �迭ó�� ����ϸ鼭 �޸𸮴� 1bit�� ���

		/// ������ Z�� ��� ��ü(����, ������..)�� �׷��ִ� ������ ���������.
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

	};
}

