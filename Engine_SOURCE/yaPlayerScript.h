#pragma once
#include "yaScript.h"
#include "yaIsaacEnums.h"

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

	public:
		void Idle();
		void Move();
		void Attack();
		void Hurt();
		void ItemAction();
		void Die();

		//void Tears(Vector3 direction);
		void Invincible();

		void gainActiveItem(class ActiveItem* item);
		void gainPassiveItem(class PassiveItem* item);
		void gainConsumable(class Pickup* pickup);
		void gainTrinket(class Trinket* pickup);

		void UseActiveItem();
		void UseConsumable();

		void ThrowConsumable();
		void ThrowTrinket();

		bool IsItemAction() { return mbItemAction; }
		bool IsGainItem() { return mbGainItem; }

	private:
		void SetGainItem(class Animator* animator);

	private:
		Transform* mTransform;
		Rigidbody* mRigidbody;

		GameObject* mHead;
		GameObject* mBody;
		GameObject* mWhole;

		GameObject* mStarflash;
		GameObject* mGainItem;

		GameObject* mGainPill;
		GameObject* mGainCard;

		float mInvincibleTime;
		float mInvincibleTimeMax;
		bool mbInvincible;

		float mItemActionTime;
		float mItemActionTimeMax;
		bool mbItemAction;

		float mDropTime;
		float mDropTimeMax;

		bool mbMove;
		
		float mGainItemTime;
		float mGainItemTimeMax;
		bool mbGainItem;

		float mAttackSpeed;
		bool mAttackAble;
	};
}
