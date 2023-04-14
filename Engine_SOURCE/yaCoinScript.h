#pragma once
#include "yaScript.h"

namespace ya
{
	class Transform;
	class Animator;
	class CoinScript : public Script
	{
	public:
		CoinScript();
		virtual ~CoinScript();

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

	private:
		void Death();

	private:
		Transform* mTransform;
		Animator* mAnimator;

		Vector3 mCollideVelocity;
	};
}
