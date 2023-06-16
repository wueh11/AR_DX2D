#pragma once
#include "yaScript.h"

namespace ya
{
	class Transform;
	class Animator;
	class Rigidbody;
	class TearScript : public Script
	{
	protected:
		enum class eState
		{
			None,
			Death,
		};

	public:
		TearScript();
		virtual ~TearScript();

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

		void Destroy();

	protected:
		Transform* mTransform;
		Animator* mAnimator;
		Rigidbody* mRigidbody;

		float mDistance;
		bool mbDead;

		eState mState;

		float mFriction;
	};
}
