#pragma once
#include "yaComponent.h"
#include "yaGameObject.h"

namespace ya
{
	using namespace math;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective, // ��������
			Orthographic,
		};
	public:
		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }

		Camera();
		~Camera();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void CreateViewMatrix();
		void CreateProjectionMatrix();

		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType layer, bool enable = true); /// ���ϴ� ��Ʈ ��ġ �� ����
		void EnableLayerMasks() { mLayerMasks.set(); } /// ���� true 
		void DisableLayerMasks() { mLayerMasks.reset(); }/// ���� false 

		void SetProjectionType(eProjectionType type) { mType = type; }

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

