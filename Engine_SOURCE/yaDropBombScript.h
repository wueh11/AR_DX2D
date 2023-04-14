#pragma once
#include "yaScript.h"

namespace ya
{
	class Transform;
	class Animator;
	class Player;
	class DropBombScript : public Script
	{
		enum class eState
		{
			Bomb,
			Explosion,
			None,
		};

	public:
		DropBombScript();
		virtual ~DropBombScript();

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

		void Imprint();
		void Explosion();
		void Death();

	public:
		Vector3 GetOwnerPos() { return mOwnerPos; }
		void SetOwnerPos(Vector3 pos) { mOwnerPos = pos; }

	private:
		Vector3 mOwnerPos;

		Transform* mTransform;
		Animator* mAnimator;

		float mAliveTime;
		eState mState;
		bool mbDead;

		bool mbEnter;
	};
}
