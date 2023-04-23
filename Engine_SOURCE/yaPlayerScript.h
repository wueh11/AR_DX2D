#pragma once
#include "yaScript.h"
#include "Isaac.h"

namespace ya
{
	using namespace isaac;
	class Transform;
	class Rigidbody;
	class PlayerScript : public Script
	{
		/*enum class st
		{
			IDLE,
			MOVE,
			ATTACK,
			ITEM,
			HURT,
			DIE,
		};*/

		struct state
		{
		};

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
		void Move();
		void Attack();
		void Hurt();
		void ItemAction();
		void Die();

		void Tears(Vector3 direction);
		void Invincible();

		void gainActiveItem(class ActiveItem* item);
		void gainConsumable(class Pickup* pickup);

		void UseActiveItem();
		void UseConsumable();

		void ThrowItem();

		bool IsItemAction() { return mbItemAction; }

	private:
		Transform* mTransform;
		Rigidbody* mRigidbody;

		GameObject* mHead;
		GameObject* mBody;

		GameObject* mStarflash;
		GameObject* mGainItem;

		float mInvincibleTime;
		float mInvincibleTimeMax;
		bool mbInvincible;

		float mItemActionTime;
		float mItemActionTimeMax;
		bool mbItemAction;

		bool mbMove;
	};
}
