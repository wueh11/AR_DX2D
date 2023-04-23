#pragma once
#include "yaEngine.h"
#include "yaScript.h"
#include "Isaac.h"

namespace ya
{
	using namespace isaac;
	class Transform;
	class Animator;
	class CardScript : public Script
	{
	public:
		CardScript();
		virtual ~CardScript();

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

	public:
		void SetCard(eCards type);

	private:
		void Take();
		void Pause();
		void Death();

	private:
		Transform* mTransform;
		Animator* mAnimator;

		eCards mCard;

		float mTimer;
		bool mbDeath;

		Vector3 mCollideVelocity;
	};
}
