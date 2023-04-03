#pragma once
#include "yaScript.h"

namespace ya
{
	class Transform;
	class Animator;
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

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

		void Idle();
		void Attack(Vector3 direction);
		void Hurt();

		void Invincible();

	private:
		Transform* mTransform;

		GameObject* mHead;
		GameObject* mBody;

		float invincibleTime;
		bool mbInvincible;
	};
}
