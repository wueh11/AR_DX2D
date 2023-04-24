#pragma once
#include "yaScript.h"
#include "Isaac.h"

using namespace ya::isaac;
namespace ya
{
	class Transform;
	class Animator;
	class PickupScript : public Script
	{
	public:
		PickupScript();
		virtual ~PickupScript();

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
		void Take();
		void Pause();
		void Death();

	protected:
		Transform* mTransform;
		Animator* mAnimator;
		eItemType mItemType;

		float mTimer;
		bool mbDeath;

		Vector3 mCollideVelocity;

		bool mbGain;
	};
}
