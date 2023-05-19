#pragma once
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer(); /// GPU에 넘겨줌

		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() { return mParent; }

		Vector3 GetPosition() { return mPosition; }
		void SetPosition(Vector3 position) { mPosition = position; }

		Vector3 GetRotation() { return mRotation; }
		void SetRotation(Vector3 rotation) { mRotation = rotation; }

		Vector3 GetScale() { return mScale; }
		void SetScale(Vector3 scale) { mScale = scale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		Matrix GetWorldMatrix() { return mWorld; }

		float GetHeight() { return mHeight; }
		void SetHeight(float height) { mHeight = height; }

	private:
		Transform* mParent;

		/// 물체의 기준이되는 기저벡터 -> 물체의 transform 체크
		Vector3 mForward; 
		Vector3 mRight;
		Vector3 mUp;

		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Matrix mWorld;

		float mHeight;
	};
}

