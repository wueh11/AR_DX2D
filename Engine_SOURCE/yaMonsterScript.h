#pragma once
#include "yaScript.h"

namespace ya
{
	class MonsterScript : public Script
	{
	public:
		MonsterScript();
		virtual ~MonsterScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void OnTriggerEnter(Collider2D* collider) override;
		virtual void OnTriggerStay(Collider2D* collider) override;
		virtual void OnTriggerExit(Collider2D* collider) override;

	protected:
		void Death();

	protected:
		bool mbHit;
		float mHitTimer;
		bool mbDeath;
		Vector3 mCollideVelocity;

		class Transform* mTransform;
		class Rigidbody* mRigidbody;
		class Animator* mAnimator;

		Vector3 mColliderPosition;
	};
}
