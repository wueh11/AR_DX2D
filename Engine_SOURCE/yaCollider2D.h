#pragma once
#include "yaComponent.h"
#include "yaTransform.h"

namespace ya
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		/// 물리 적용
		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		eColliderType GetColliderType() { return mType; }
		void SetColliderType(eColliderType type) { mType = type; }

		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetSize() { return mSize; }

		void SetPosition(Vector3 position) { mPosition = position; }
		Vector3 GetPosition() { return mPosition; }

		void SetCenter(Vector2 center) { mCenter = center; }
		Vector2 GetCenter() { return mCenter; }

		void SetRadius(float radius) { mRadius = radius; }

		bool IsTrigger() { return mbTrigger; }
		UINT GetID() { return mID; }

	private:
		static UINT mColliderNumber; /// 같은 레이어간의 충돌 상태를 방지하기위해
		UINT mID;

		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mPosition;
		float mRadius;

		bool mbTrigger;
	};
}

