#pragma once
#include "yaComponent.h"
#include "yaCollider2D.h"
/// monobehavior
namespace ya
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

	public:
		void Shadow(Vector3 pos = Vector3::Zero, Vector3 scale = Vector3::One);
		void SetShadowPosition(Vector3 pos);
		void SetShadowScale(Vector3 scale);

	protected:
		GameObject* mShadow;
		Vector3 mShadowPos;
		Vector3 mShadowScale;
	};
}

