#pragma once
#include "yaScript.h"

namespace ya
{
	class Transform;
	class Animator;
	class Player;
	class BombScript : public Script
	{
		enum class eState
		{
			Bomb,
			Explosion,
			Imprint,
			None,
		};

	public:
		BombScript();
		virtual ~BombScript();

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

		void Explosion();
		void Imprint();

	public:
		Vector3 GetOwnerPos() { return mOwnerPos; }
		void SetOwnerPos(Vector3 pos) { mOwnerPos = pos; }

	private:
		Vector3 mOwnerPos;

		Transform* mTransform;
		Animator* mAnimator;

		GameObject* mEffect;

		float mAliveTime;
		eState mState;
		bool mbDead;
	};
}
